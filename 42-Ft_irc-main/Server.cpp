/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:39:13 by eakman            #+#    #+#             */
/*   Updated: 2025/03/16 22:39:13 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Commands.hpp"
#include <sstream>

// Constructor port ve password atanır server_socket başta geçersiz olacak şekilde -1 olarak ayarlanır (henüz socket açılmadı)
Server::Server(int port, const std::string& password): port(port), server_socket(-1), password(password) {}

Server::~Server() {
    if (server_socket != -1) {
        close(server_socket);
    }
}

bool Server::isAuthorized(int fd) const { return authorizedClients.find(fd) != authorizedClients.end(); }
void Server::authorizeClient(int fd) { authorizedClients.insert(fd); }
const std::string& Server::getPassword() const { return password; }

void Server::init() {
    std::cout << "✅ Initializing the server..." << std::endl;

    // Sunucu socket'i oluşturuluyor (IPv4, TCP)
    // AF_INET	IPv4 adres ailesi (yani soket IPv4 kullanacak)
    // SOCK_STREAM	TCP bağlantısı olacak (veri akışı güvenli ve sıralı olacak)
    // IPPROTO_TCP	TCP protokolü kullanılacak (genelde 6'dır, açıkça belirtilmiş)
    // socket() başarılı olursa: pozitif bir integer döner (dosya tanımlayıcısı – socket FD)
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "❌ Error: Failed to create socket!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Aynı portun kısa sürede yeniden kullanılabilmesini sağlamak için socket ayarı yapılıyor (SO_REUSEADDR).
    // Bu ayar olmadan sunucu kapatılıp hemen tekrar başlatıldığında "address already in use" hatası alınabilir.
    int opt = 1;

    // setsockopt(): Socket'e özel ayarlar uygular.
    // - SOL_SOCKET → socket seviyesinde bir ayar yapılacağını belirtir
    // - SO_REUSEADDR → aynı adresin (IP:port) yeniden kullanılmasına izin verir
    // - &opt → ayarın değeri (1 = true, etkin)
    // - sizeof(opt) → ayar değerinin bayt cinsinden boyutu
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "❌ Error: Failed to set socket settings!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Sunucu adresi yapılandırılıyor
    memset(&server_addr, 0, sizeof(server_addr)); // Yapıyı sıfırla
    server_addr.sin_family = AF_INET;             // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;     // Her IP'den bağlantı kabul et →  0.0.0.0
    server_addr.sin_port = htons(port);           // Port numarası (ağ byte sırası)
    // htons fonksiyonu Bilgisayarının (host) içindeki veriyi
    // Ağın kullandığı standart biçime (network byte order) çevirir.
    
    // Adres socket'e bağlanıyor
    // Sunucunun hangi IP ve port'ta dinleyeceğini işletim sistemine bildirir.
    // bind() → daha önce socket() ile oluşturulmuş olan soketi belirli bir IP adresine ve port numarasına bağlar.
    // Böylece sistem, bu IP:port üzerinden gelen bağlantıları bu sokete yönlendirmeye başlar.
    // (struct sockaddr *)&server_addr → IPv4 adres yapısını, sistem fonksiyonlarının anlayacağı genel adrese dönüştür
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "❌ Error: Binding (bind) failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

       // Socket dinlemeye alınıyor (connection kuyruğu: 10)
    // Connection kuyruğu, istemciler sunucuya bağlanmaya çalıştığında, sunucu henüz onları kabul (accept()) edememişken, bu isteklerin geçici olarak bekletildiği listedir.
    if (listen(server_socket, 10) == -1) {
        std::cerr << "❌ Error: Listen failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "✅ Server initialized! Port: " << port << std::endl;
}

void Server::run() {

    // Sunucu socket'i için pollfd nesnesi hazırlanır
    struct pollfd server_pollfd;
    server_pollfd.fd = server_socket;   // Dinlenen socket
    server_pollfd.events = POLLIN;      // Veri geldiğinde haberdar et
    clients.push_back(server_pollfd);   // clients listesine ekle (ilk eleman server olacak)

    // Sonsuz döngü: Sunucu çalıştığı sürece istemcileri dinle
    while (true) {

        // poll() ile tüm bağlantılar izleniyor
        if (poll(clients.data(), clients.size(), -1) == -1) {
            std::cerr << "❌ Error: poll() failed!" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Eğer server socket'e yeni bağlantı isteği geldiyse
        if (clients[0].revents & POLLIN) {
            acceptClient(); // Yeni istemciyi kabul et
        }

        // Diğer tüm client soketlerini kontrol et
        for (size_t i = 1; i < clients.size(); i++) {
            if (clients[i].revents & POLLIN) {
                receiveMessage(clients[i].fd);  // Bu client'tan gelen mesajı işle
            }
        }
    }
}

void Server::acceptClient() {

    // Yeni istemcinin adresini tutmak için yapı oluşturuluyor
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    // accept(): Bağlantıyı kabul et ve yeni bir socket FD döndür
    int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);

    if (client_socket == -1) {
        std::cerr << "❌ Error: Failed to accept client connection!" << std::endl;
    } else {
         // Yeni istemci başarıyla bağlandı
        std::cout << "✅ New client connected! (Socket FD: " << client_socket << ")" << std::endl;

        // poll listesine yeni istemciyi ekle (POLLIN: veri geldiğinde haber ver)
        struct pollfd new_client;
        new_client.fd = client_socket;
        new_client.events = POLLIN;
        clients.push_back(new_client);

        // İstemciye hoş geldin mesajı gönder
        std::string welcome_msg = ":ft_irc 001 NewUser :Welcome to ft_irc Server!\r\n";
        send(client_socket, welcome_msg.c_str(), welcome_msg.size(), 0);
    }
}

void Server::receiveMessage(int client_fd) 
{

    // 4096 baytlık bir buffer oluşturulur (IRC mesaj limiti)
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer)); // Buffer içeriği sıfırlanır

    // Belirtilen client socket'ten veri alınır
    // recv(), bir socket üzerinden gelen veriyi okumak (almak) için kullanılan sistem çağrısıdır.
    int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    // Eğer bağlantı kapandıysa ya da hata oluştuysa
    if (bytes_received <= 0) {
        removeClient(client_fd); // İstemci bağlantısı kesilir ve listeden çıkarılır
    }
    else {
        // Partial data handling
        clientBuffers[client_fd] += std::string(buffer, bytes_received);

        // Mesajları \r\n ile ayır
        size_t pos = 0;
        while ((pos = clientBuffers[client_fd].find("\r\n")) != std::string::npos) {
            std::string message = clientBuffers[client_fd].substr(0, pos);
            clientBuffers[client_fd] = clientBuffers[client_fd].substr(pos + 2);

            if (!message.empty()) {
                std::cout << "📩 Message received from client: " << message << std::endl;
                // Mesaj, komut yorumlayıcıya gönderilir
                Commands::processMessage(*this, client_fd, message);
            }
        }
    }
}

void Server::removeClient(int client_fd) {

    // Bağlantıyı kapatan istemci hakkında bilgi ver
    std::cout << "❌ The client has closed the connection! (Socket FD: " << client_fd << ")" << std::endl;
    
    // Socket bağlantısını kapat
    close(client_fd);

    // Client buffer'ını temizle
    clientBuffers.erase(client_fd);

     // pollfd listesinde bu istemciyi bul ve sil
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].fd == client_fd) {
            clients.erase(clients.begin() + i); // İlgili pollfd öğesini sil
            break;
        }
    }

    // Bu istemciye ait nickname bilgisini de sil
    nicknames.erase(client_fd);
}

void Server::sendToChannel(const std::string& channel, const std::string& sender, const std::string& message, int sender_fd, bool isCommand) {

    // IRC formatına uygun mesaj oluşturuluyor
    std::string full_message = ":" + sender + " PRIVMSG " + channel + " :" + message + "\r\n";

    // Eğer kanal mevcut değilse hata verip çık
    if (channels.find(channel) == channels.end()) {
        std::cerr << "❌ Error: Channel not found!" << std::endl;
        return;
    }

    // Kanalda bulunan tüm istemcilere mesaj gönder
    for (std::set<int>::iterator it = channels[channel].begin(); it != channels[channel].end(); ++it) {
        
        // Gönderen istemci hariç herkese mesajı gönder
        if (*it != sender_fd) {
            send(*it, full_message.c_str(), full_message.size(), 0);
            std::cout << "📨 Message sent: " << full_message << std::endl;
        }

        // Eğer bu bir komutsa, gönderen kişiye de mesajı göster (örneğin: /me veya sunucu komutu)
        else if (isCommand && sender_fd == *it) {
            std::cout << "📨 Command sent: " << full_message << std::endl;
            send(*it, full_message.c_str(), full_message.size(), 0);
        }

        // Ne mesaj ne komut olarak gönderilmesi gerekiyorsa logla ama gönderme
        else {
            std::cout << "📨 No message was sent: " << full_message << std::endl;
        }
    }
}

void Server::createChannel(const std::string& channelName, int client_fd) {
    channels[channelName].insert(client_fd);
    channelFounders[channelName] = client_fd;
}

int Server::getUserFdByNick(const std::string& nickname) {
    for (size_t i = 0; i < clients.size(); ++i) {
        int fd = clients[i].fd;
        if (nicknames.find(fd) != nicknames.end()) {
            if (strcasecmp(nicknames[fd].c_str(), nickname.c_str()) == 0)
                return fd;
        }
    }
    return -1;
}

std::vector<struct pollfd>& Server::getClients()                     { return clients; }
std::map<int, std::string>& Server::getNicknames()                   { return nicknames; }
std::map<std::string, int>& Server::getChannelLimits()               { return channelLimits; }
std::set<std::string>& Server::getInviteOnlyChannels()               { return inviteOnlyChannels; }
std::map<std::string, int>& Server::getChannelFounders()             { return channelFounders; }
std::map<std::string, std::set<int> >& Server::getChannels()         { return channels; }
std::map<std::string, std::string>& Server::getChannelKeys()         { return channelKeys; }
std::map<std::string, std::string>& Server::getChannelModes()        { return channelModes; }
std::map<std::string, std::string>& Server::getChannelTopics()       { return channelTopics; }
std::map<std::string, std::set<int> >& Server::getInvitedUsers()     { return invitedUsers; }
std::map<std::string, std::set<int> >& Server::getChannelOperators() { return channelOperators; }
