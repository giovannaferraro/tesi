#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include "/home/haura/Downloads/tesi_riccio_giovanna/cpp-httplib/httplib.h"
#include <nlohmann/json.hpp>


using json = nlohmann::json;
using namespace std;

std::string calculate_sha256(const std::string& input) {

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, input.c_str(), input.length());
    SHA256_Final(hash, &sha256_ctx);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main() {
    // Initialize variables manually as they are no longer taken from cloud
    std::string messageID = "2";
    std::string timestamp = "Thu Mar 11 17:21:11 CET 2024";
    std::string messageBodyFormat = "UPER";
    std::string messageType = "CAM";
    std::string messageDirection = "Upstream";
    int repetitionDuration = 600;
    int repetitionInterval = 1000;
    std::string messageBody = "02020000670e89d8005a0d70ee4e3af9f522342308e433c8545803e0e2458302968a7b35818224c2104700197980";
    
    // Calculate hash
    std::string hash = calculate_sha256(messageBody);


    // Create JSON object
    json json_to_send = {
        {"messageId", messageID},
        {"timestamp", timestamp},
        {"hash", hash},
        {"messageBodyFormat", messageBodyFormat},
        {"messageType", messageType},
        {"messageDirection", messageDirection},
        {"repetitionDuration", repetitionDuration},
        {"repetitionInterval", repetitionInterval},
        {"messageBody", messageBody}
    };

    // Setup HTTP client
    std::string ip_address = "10.0.1.157";  // Replace with actual IP address
    // Consider using environment variables or a secure method for credentials
    std::string username = "root";
    std::string password = "password";

    httplib::Client cli("http://" + ip_address);

    // Set basic authentication (if using credentials)
    cli.set_basic_auth(username, password);

    // Make POST request
    try {
      auto response = cli.Post("/proxy/msg", json_to_send.dump(), "application/json");
      if (response->status == 200 ) {
          // Handle response
          //std::cout << "Response status: " << response->status << std::endl;
          //std::cout << "Response body: " << response->body << std::endl;
          std::cout << "Successfully received a response!" << std::endl;
      } 

    } catch(const std::exception& e) {
      std::cerr << "Error making request: " << e.what() << std::endl;
    }
    
    return 0;
}