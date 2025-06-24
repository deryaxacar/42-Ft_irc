/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakman <arcemirhanakman@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:31:51 by eakman            #+#    #+#             */
/*   Updated: 2025/03/16 22:31:51 by eakman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cerrno>  
#include <climits> 

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "❌ Usage: ./ircserv <port> <password>" << std::endl;
        return EXIT_FAILURE;
    }

    char* endPtr = NULL;
    // önceki sistem çağrılarından kalmış olası hata kodlarını temizler. strtol
    errno = 0;
    // string’ini long türüne dönüştürür çünkü string ile port dinlenmez.
    // 10 → onluk (decimal) sayı sisteminde çözümlemesini söyler
    // endPtr → dönüşüm sonrası kalan karakteri gösterir (örneğin "6667abc" olursa 'a')
    long port = strtol(argv[1], &endPtr, 10);
    
    // Port geçerlilik kontrolü en yüksek kullanılabilir port 65535
    if (errno != 0 || *endPtr != '\0' || port <= 0 || port > 65535) {
        std::cerr << "❌ Error: Invalid port number. Port must be between 1 and 65535." << std::endl;
        return EXIT_FAILURE;
    }
    // Örnek: "./ircserv 6667 deneme" →  password = "deneme"
    std::string password = argv[2];
    // verilen port ve şifre bilgisiyle bir IRC sunucusu nesnesi oluştur ve çalışmaya hazırla.
    Server server(port, password);  
    server.init();
    server.run();
    return 0;
}
