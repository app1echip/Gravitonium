#ifndef GRAVITONIUM_CLIENT_H
#define GRAVITONIUM_CLIENT_H

#include "../Play/Play.h"
#include <SFML/Network.hpp>

class Client : public Play {
private:
    enum ClientStatus {
        FindHost, WaitInLobby, SelectCharacter, Playing
    };
    ClientStatus clientStatus;
    sf::UdpSocket socket;
    unsigned short localPort;
    sf::IpAddress hostIP;
    unsigned short hostPort;

    sf::Thread clientThread;

    void clientMain();

    std::vector<std::string> tmplist;
    std::string tMap;
    std::vector<int> action;

    void handleInputFindHost();

    void handleInputWaitInLobby();

    void handleInputPlaying();

    void updateFindHost(float);

    void updateWaitInLobby(float);

    void drawFindHost() const;

    void drawWaitInLobby() const;

    void processRawIP(const std::string &, sf::IpAddress &, unsigned short &);

    bool requestJoin = false;

    void sendRequest();

    void uploadControl();

    void acceptPos();


    void mirrorPlayer();

    void mirrorMap();

    bool listenForReady();

public:
    void handleInput();

    void update(float);

    void draw() const;

    Client(Game *);
};

#endif //GRAVITONIUM_CLIENT_H
