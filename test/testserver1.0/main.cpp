#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/Network.hpp>

void handleRequest(sf::TcpSocket& client) {
    // �ӿͻ��˶�ȡ HTTP ����
    std::string requestString;
    char buffer[1024];
    std::size_t received = 0;
    while (client.receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
        requestString.append(buffer, received);
        if (requestString.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }

    // ���� HTTP ����ͷ
    std::istringstream iss(requestString);
    std::string method, uri, version;
    iss >> method >> uri >> version;
    std::string headerLine;
    std::string contentLength;
    while (std::getline(iss, headerLine) && headerLine != "\r") {
        if (headerLine.substr(0, 14) == "Content-Length") {
            contentLength = headerLine.substr(16);
        }
    }

    // ���������ж�ȡ����
    std::string requestBody;
    if (!contentLength.empty()) {
        std::size_t bodySize = std::stoi(contentLength);
        requestBody.resize(bodySize);
        if (client.receive(&requestBody, bodySize, received) != sf::Socket::Done) {
            // ��ȡ������ʧ��
            return;
        }
    }

    // ���� HTTP ��Ӧ
    std::ostringstream oss;
    std::ostringstream osss;
    std::string htmlpage;
    std::ifstream file("Test.html");
    for (; file.peek() > 0;)
    {
        file >> htmlpage;
        //std::cout << htmlpage << std::endl;
        osss << htmlpage << std::endl;
    }
    oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << osss.str().size() << "\r\n";
    oss << "\r\n";
    oss << osss.str();

    // ���� HTTP ��Ӧ
    std::string responseString = oss.str();
    std::cout << responseString << std::endl;
    client.send(responseString.c_str(), responseString.size());
}

int main() {
    sf::TcpListener listener;
  listener.listen(8080);

  // 等待连接并处理请求
  while (true) {
    sf::TcpSocket client;
    listener.accept(client);
    handleRequest(client);
  }

    return 0;
}