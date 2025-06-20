#include "Privmsg.hpp"
#include "../Commands.hpp"

namespace Commands
{

    void privmsgCommand(Server &server, int client_fd, std::istringstream &iss)
    {
        std::string target, msg;
        iss >> target;
        std::getline(iss, msg);

        if (!server.isAuthorized(client_fd))
        {
            std::string msg = ":ft_irc 462 :You not register\r\n";
            send(client_fd, msg.c_str(), msg.size(), 0);
            return;
        }

        if (msg.empty() || msg.find_first_not_of(" ") == std::string::npos)
        {
            std::string error_msg = ":ft_irc 400 PRIVMSG :Invalid message format. Usage: PRIVMSG <target> :message\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        msg = msg.substr(msg.find_first_not_of(" :"));

        if (target.empty())
        {
            std::string error_msg = ":ft_irc 411 :No recipient given (PRIVMSG)\r\n";
            send(client_fd, error_msg.c_str(), error_msg.size(), 0);
            return;
        }

        if (target[0] == '#')
        {
            if (server.getChannels().find(target) == server.getChannels().end())
            {
                std::string error_msg = ":ft_irc 403 PRIVMSG :No such channel\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }

            if (server.getChannels()[target].find(client_fd) == server.getChannels()[target].end())
            {
                std::string error_msg = ":ft_irc 404 PRIVMSG :You are not in this channel\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }

            std::cout << "🔍 DEBUG: privmsgCommand has been invoked! Target " << target << ", Message: " << msg << std::endl;
            server.sendToChannel(target, server.getNicknames()[client_fd], msg, client_fd);
        }
        else
        {
            int targetFd = server.getUserFdByNick(target);
            if (targetFd == -1)
            {
                std::string error_msg = ":ft_irc 401 " + target + " :No such nick\r\n";
                send(client_fd, error_msg.c_str(), error_msg.size(), 0);
                return;
            }

            std::string msgToSend = ":" + server.getNicknames()[client_fd] + " PRIVMSG " + target + " :" + msg + "\r\n";
            send(targetFd, msgToSend.c_str(), msgToSend.size(), 0);
        }
    }

}
