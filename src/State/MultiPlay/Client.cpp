//
// Created by aya on 7/11/2019.
//

#include "Client.h"
#include <windows.h>
#include <map>
#include <iostream>

extern const float WindowScale;

Client::Client(Game *pGame) : Play(pGame), clientThread(&Client::clientMain, this),
                              clientStatus(Client::ClientStatus::FindHost) {
    clientThread.launch();
    setWidget("FindHost");
}

void Client::clientMain() {
    socket.bind(sf::Socket::AnyPort);
    localPort = socket.getLocalPort();
    socket.setBlocking(false);


    bool stop = false;
    bool widgetSet = false;
    while (!stop) {
        switch (clientStatus) {
            case Client::ClientStatus::FindHost:
                if (requestJoin) {
                    sendRequest();
                    requestJoin = false;
                    clientStatus = Client::ClientStatus::WaitInLobby;
                }
                Sleep(60);
                break;
            case Client::ClientStatus::WaitInLobby:
                setWidget("WaitInLobby");
                mirrorPlayer();
                mirrorMap();
                if (listenForReady()) {
                    for (auto &item:tmplist) {
                        addCharacter(item);
                        character[item]->setCharacter("RedBoy", "SMG");
                    }
                    map.setMap(tMap);
                    clientStatus = SelectCharacter;
                }
                Sleep(30);
                break;
            case Client::ClientStatus::SelectCharacter:
                Sleep(50);
                break;
            case Client::ClientStatus::Playing:
                uploadControl();
                acceptPos();
                break;
        }
    }
}

bool Client::listenForReady() {
    sf::Packet packet;
    sf::IpAddress tIP;
    unsigned short tPort;
    socket.receive(packet, tIP, tPort);

    std::string declare;
    packet >> declare;
    bool result = false;
    if (declare == "ready") {
        packet >> result;
    }
    return result;
}

void Client::handleInput() {
    switch (clientStatus) {
        case Client::ClientStatus::FindHost:
            handleInputFindHost();
            break;
        case Client::ClientStatus::WaitInLobby:
            handleInputWaitInLobby();
            break;
        case Client::ClientStatus::SelectCharacter:
            handleInputSelectCharacter();
            if (status == Play::Status::Playing) clientStatus = Playing;
            break;
        case Client::ClientStatus::Playing:
            handleInputPlaying();
            break;
    }
}

void Client::handleInputFindHost() {
    sf::Event event;
    std::string rawIP = widget[1]->getMessage();
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
            case sf::Event::TextEntered:
                rawIP += event.text.unicode;
                widget[1]->setMessage(rawIP);
                break;
            case sf::Event::MouseButtonPressed:
                auto mousePos = sf::Mouse::getPosition(game->window);
                mousePos = sf::Vector2i(mousePos.x / WindowScale, mousePos.y / WindowScale);
                for (auto item:widget)
                    if (item->contain(mousePos)) {
                        switch (item->call) {
                            case 2:
                                processRawIP(rawIP, hostIP, hostPort);
                                requestJoin = true;
                                break;
                        }
                        break;
                    }
                break;
        }
    }
}

void Client::handleInputWaitInLobby() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
        }
    }
}

void Client::handleInputPlaying() {
    sf::Event event;
    while (game->window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                game->window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Space:
                        action.push_back(3);
                        break;
                    case sf::Keyboard::A:
                        action.push_back(1);
                        break;
                    case sf::Keyboard::D:
                        action.push_back(2);
                        break;
                    case sf::Keyboard::S:
                        action.push_back(4);
                        break;
                    case sf::Keyboard::K:
                        action.push_back(5);
                        character["player" + std::to_string(localPort)]->shoot();
                        break;
                    case sf::Keyboard::Escape:
                        game->popState();
                        return;
                }
                break;
        }
    }
}

void Client::update(float dt) {
    switch (clientStatus) {
        case Client::ClientStatus::FindHost:
            updateFindHost(dt);
            break;
        case Client::ClientStatus::WaitInLobby:
            updateWaitInLobby(dt);
            break;
        case Client::ClientStatus::SelectCharacter:
            updateSelectCharacter(dt);
            break;
        case Client::ClientStatus::Playing:
            updatePlaying(dt);
            break;
    }
}

void Client::updateFindHost(float dt) {

}

void Client::updateWaitInLobby(float dt) {
    widget[0]->setMessage(map.getMapName());
    std::string all;
    for (auto &item:tmplist)
        all += item + " ";
    widget[1]->setMessage(all);
}

void Client::draw() const {
    switch (clientStatus) {
        case Client::ClientStatus::FindHost:
            drawFindHost();
            break;
        case Client::ClientStatus::WaitInLobby:
            drawWaitInLobby();
            break;
        case Client::ClientStatus::SelectCharacter:
            drawSelectCharacter();
            break;
        case Client::ClientStatus::Playing:
            drawPlaying();
            break;
    }
}

void Client::drawFindHost() const {
    for (auto item:widget)
        game->window.draw(*item);
}

void Client::drawWaitInLobby() const {
    for (auto item:widget)
        game->window.draw(*item);
}

void Client::processRawIP(const std::string &raw, sf::IpAddress &ip, unsigned short &port) {
    ip = raw.substr(0, raw.find(':'));
    port = stoi(raw.substr(raw.find(":") + 1));
}

void Client::sendRequest() {
    sf::Packet packet;
    std::string name = "player" + std::to_string(localPort);
    packet << name;
    socket.send(packet, hostIP, hostPort);
}

void Client::uploadControl() {
    while (!action.empty()) {
        sf::Packet packet;
        packet << "control" << action[0];
        socket.send(packet, hostIP, hostPort);
        action.erase(action.begin());
    }
}

void Client::acceptPos() {
    sf::Packet packet;
    std::string declare;
    sf::IpAddress tIP;
    unsigned short tPort;
    socket.receive(packet, tIP, tPort);
    packet >> declare;
    if (declare == "pos") {
        int n;
        packet >> n;
        for (int i = 0; i < n; ++i) {
            std::string target;
            float x, y;
            int index;
            packet >> target >> x >> y >> index;
            character[target]->setFacing(index == -1 ? BaseObject::Direction::Left : BaseObject::Direction::Right);
            b2Body *targetBody = character[target]->mBody;
            targetBody->SetLinearVelocity(b2Vec2(0, 0));
            targetBody->SetTransform(b2Vec2(x, y), targetBody->GetAngle());
        }
    }
}

void Client::mirrorPlayer() {
    sf::Packet packet;
    sf::IpAddress tIP;
    unsigned short tPort;
    socket.receive(packet, tIP, tPort);

    std::string declare, inName;
    packet >> declare;
    if (declare == "charas") {
        tmplist.clear();
        int size;
        packet >> size;
        for (int i = 0; i < size; i++) {
            std::string name;
            packet >> name;
            tmplist.push_back(name);
        }
    }
}

void Client::mirrorMap() {
    sf::Packet packet;
    sf::IpAddress tIP;
    unsigned short tPort;
    socket.receive(packet, tIP, tPort);

    std::string declare, inName;
    packet >> declare;
    if (declare == "map") {
        packet >> tMap;
    }
}