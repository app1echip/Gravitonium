#include "Server.h"
#include <windows.h>
#include <iostream>

extern const float WindowScale;

Server::Server(Game *pGame) : Play(pGame), serverThread(&Server::serverMain, this),
                              serverStatus(Server::ServerStatus::SelectMap) {
    serverThread.launch();
    addCharacter("Pedro");
    character["Pedro"]->setCharacter("RedBoy", "SMG");
}

void Server::serverMain() {
    localPort = 6666;
    socket.bind(localPort);
    socket.setBlocking(false);
    bool running = true;
    ready = false;
    while (running) {
        switch (serverStatus) {
            case Server::ServerStatus::SelectMap:
                Sleep(50);
                break;
            case Server::ServerStatus::WaitInLobby:
                serverAcceptPlayer();
                broadCastPlayerList();
                broadCastMap();
                if (ready) {
                    broadCastReady();
                    serverStatus = Server::ServerStatus::SelectCharacter;
                }
                Sleep(60);
                break;
            case Server::ServerStatus::SelectCharacter:
                Sleep(50);
                break;
            case Server::ServerStatus::Playing:
                acceptControl();
                broadcastPosition();
                break;
        }
    }
}

void Server::broadcastPosition() {
    sf::Packet packet;
    packet << "pos" << character.size();
    for (auto &item:character)
        packet << item.first << item.second->mBody->GetPosition().x << item.second->mBody->GetPosition().y
               << item.second->horizontalIndex[item.second->facing];
    for (auto &item:playerIP)
        socket.send(packet, item.second.first, item.second.second);
}

void Server::acceptControl() {
    sf::Packet packet;
    unsigned short tPort;
    sf::IpAddress tIP;
    socket.receive(packet, tIP, tPort);
    std::string declare;
    packet >> declare;
    if (declare == "control") {
        std::string target = "player" + std::to_string(tPort);
        int cmd;
        packet >> cmd;
        switch (cmd) {
            case 1:
                character[target]->move(Character::Direction::Left);
                break;
            case 2:
                character[target]->move(Character::Direction::Right);
                break;
            case 3:
                character[target]->move(Character::Direction::Up);
                break;
            case 4:
                character[target]->move(Character::Direction::Down);
                break;
            case 5:
                character[target]->shoot();
                break;
        }
    }
}

void Server::serverAcceptPlayer() {
    std::string playerName;
    sf::IpAddress ip;
    unsigned short port;
    sf::Packet packet;
    socket.receive(packet, ip, port);
    packet >> playerName;
    if (playerName != "") {
        addCharacter(playerName);
        character[playerName]->setCharacter("RedBoy", "SMG");
        playerIP[playerName] = std::make_pair(ip, port);
    }
}

void Server::broadCastPlayerList() {
    sf::Packet allpacket;
    allpacket << "charas" << character.size();
    for (auto &item:character)
        allpacket << item.first;
    for (auto &item:playerIP)
        socket.send(allpacket, item.second.first, item.second.second);
}

void Server::broadCastMap() {
    sf::Packet allpacket;
    allpacket << "map" << map.getMapName();
    for (auto &item:playerIP)
        socket.send(allpacket, item.second.first, item.second.second);
}

void Server::broadCastReady() {
    sf::Packet packet;
    packet << "ready" << true;
    for (auto &item:playerIP)
        socket.send(packet, item.second.first, item.second.second);
}

void Server::handleInput() {
    switch (serverStatus) {
        case Server::ServerStatus::SelectMap:
            handleInputSelectMap();
            if (status == Play::Status::SelectCharacter) {
                serverStatus = WaitInLobby;
                setWidget("WaitInLobby");
            }
            break;
        case Server::ServerStatus::WaitInLobby:
            handleInputWaitInLobby();
            break;
        case Server::ServerStatus::SelectCharacter:
            handleInputSelectCharacter();
            if (status == Play::Status::Playing) serverStatus = Server::ServerStatus::Playing;
            break;
        case Server::ServerStatus::Playing:
            handleInputPlaying();
            break;
    }
}

void Server::handleInputWaitInLobby() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
            case sf::Event::MouseButtonPressed:
                auto mousePos = sf::Mouse::getPosition(game->window);
                mousePos = sf::Vector2i(mousePos.x / WindowScale, mousePos.y / WindowScale);
                for (auto item:widget)
                    if (item->contain(mousePos)) {
                        switch (item->call) {
                            case 0:
                                ready = true;
                                break;
                        }
                        break;
                    }
                break;
        }
    }
}

void Server::update(float dt) {
    switch (serverStatus) {
        case Server::ServerStatus::SelectMap:
            updateSelectMap(dt);
            break;
        case Server::ServerStatus::WaitInLobby:
            updateWaitInLobby(dt);
            break;
        case Server::ServerStatus::SelectCharacter:
            updateSelectCharacter(dt);
            break;
        case Server::ServerStatus::Playing:
            updatePlaying(dt);
            break;
    }
}

void Server::updateWaitInLobby(float) {
    std::string all;
    for (auto &item:character)
        all += item.first + " ";
    widget[0]->setMessage(all);
}

void Server::draw() const {
    switch (serverStatus) {
        case Server::ServerStatus::SelectMap:
            drawSelectMap();
            break;
        case Server::ServerStatus::WaitInLobby:
            drawWaitInLobby();
            break;
        case Server::ServerStatus::SelectCharacter:
            drawSelectCharacter();
            break;
        case Server::ServerStatus::Playing:
            drawPlaying();
            break;
    }
}

void Server::drawWaitInLobby() const {
    for (auto item:widget)
        game->window.draw(*item);
}