/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deryacar <deryacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:16:16 by deryacar          #+#    #+#             */
/*   Updated: 2025/06/24 16:16:16 by deryacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Modes/Modes.hpp"
#include <signal.h>
#include <iostream>
#include <sstream>
#include <cctype>

static std::string toUpper(const std::string &str)
{
    std::string result = str;
    for (size_t i = 0; i < result.length(); ++i)
        result[i] = std::toupper(result[i]);
    return result;
}

// Sunucudan gelen bir mesajı işler ve uygun komut fonksiyonunu çağırır.
void Commands::processMessage(Server &server, int client_fd, const std::string &message)
{
    std::istringstream iss(message);           // Mesajı boşluklara göre ayrıştırmak için string stream kullanılır
    std::string command;
    iss >> command;                            // İlk kelime komut olarak alınır
    command = toUpper(command);                // Komut büyük harfe çevrilerek karşılaştırma yapılabilir hale getirilir

    // Gelen komutun türüne göre uygun fonksiyon çağrılır
    if (command == "PASS")                     // Bağlantı için şifre doğrulama komutu
    {
        passCommand(server, client_fd, iss);
        return;                                // PASS komutu özel olduğu için işlem burada sonlandırılır
    }
    else if (command == "NICK")                // Kullanıcı takma adı belirleme komutu
        nickCommand(server, client_fd, iss);
    else if (command == "USER")                // Kullanıcı adı ve diğer bilgileri ayarlama komutu
        userCommand(server, client_fd, iss);
    else if (command == "JOIN")                // Kanal katılım komutu
        joinCommand(server, client_fd, iss);
    else if (command == "PART")                // Kanaldan ayrılma komutu
        partCommand(server, client_fd, iss);
    else if (command == "QUIT")                // IRC sunucusundan çıkış komutu
        quitCommand(server, client_fd, iss);
    else if (command == "MODE")                // Kanal modlarını değiştirme komutu
        modeCommand(server, client_fd, iss);
    else if (command == "KICK")                // Kanal dışına kullanıcı atma komutu
        kickCommand(server, client_fd, iss);
    else if (command == "TOPIC")               // Kanalın başlığını değiştirme/görüntüleme komutu
        topicCommand(server, client_fd, iss);
    else if (command == "INVITE")              // Başka kullanıcıyı kanala davet etme komutu
        inviteCommand(server, client_fd, iss);
    else if (command == "PRIVMSG")             // Özel mesaj veya kanal mesajı gönderme komutu
        privmsgCommand(server, client_fd, iss);
    else {
        // Bilinmeyen komut için istemciye hata mesajı gönderilir
        std::string error_msg = ":ft_irc 421 " + command + " :Unknown command\r\n";
        send(client_fd, error_msg.c_str(), error_msg.size(), 0);

        // Sunucu tarafında da bilinmeyen komut loglanır
        std::cout << "❗ Unknown command: " << command << " from client " << client_fd << "\n";
    }
}

