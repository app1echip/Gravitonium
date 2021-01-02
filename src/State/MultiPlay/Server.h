#ifndef GRAVITONIUM_SERVER_H
#define GRAVITONIUM_SERVER_H

#include "../Play/Play.h"
#include <SFML/Network.hpp>

class Server : public Play {
private:
    enum ServerStatus {
        SelectMap, WaitInLobby, SelectCharacter, Playing
    };
    ServerStatus serverStatus;
    sf::UdpSocket socket;
    unsigned short localPort;
    sf::Thread serverThread;

    void serverMain();

    void serverAcceptPlayer();

    typedef std::pair<sf::IpAddress, unsigned short> PlayerIP;

    void acceptControl();

    std::unordered_map<std::string, PlayerIP> playerIP;

    bool ready;

    void handleInputWaitInLobby();

    void updateWaitInLobby(float);

    void drawWaitInLobby() const;

    void broadCastPlayerList();

    void broadCastMap();

    void broadCastReady();

    void broadcastPosition();

public:

    Server(Game *);

    virtual void handleInput();

    virtual void update(float);

    virtual void draw() const;
};

#endif //GRAVITONIUM_SERVER_H