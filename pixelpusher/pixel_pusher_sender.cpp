#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <asio.hpp>
#include <thread>

using asio::ip::udp;

class Discovery {
public:

  std::string mac_address() {
    char buf[64];

    sprintf(buf, "%02x:%02x:%02x:%02x:%02x:%02x",
      packet.mac_address[0], packet.mac_address[1], packet.mac_address[2],
      packet.mac_address[3], packet.mac_address[4], packet.mac_address[5]);
    return std::string(buf);
  }

  std::string ip_address() {
    char buf[64];

    sprintf(buf, "%d.%d.%d.%d",
      packet.ip_address[0], packet.ip_address[1], packet.ip_address[2], packet.ip_address[3]);
    return std::string(buf);
  }

  void print() {
    printf(" mac_address: %s\n", mac_address().c_str());

    printf(" ip_address: %d.%d.%d.%d\n", 
      packet.ip_address[0], packet.ip_address[1], packet.ip_address[2], packet.ip_address[3]);
    printf(" device_type: %d\n", packet.device_type);
    printf(" protocol_version: %d\n", packet.protocol_version);
    printf(" vendor_id: %d\n", packet.vendor_id);
    printf(" product_id: %d\n", packet.product_id);
    printf(" hw_revision: %d\n", packet.hw_revision);
    printf(" sw_revision: %d\n", packet.sw_revision);
    printf(" link_speed: %d\n", packet.link_speed);
    printf(" strips_attached: %d\n", packet.strips_attached) ;
    printf(" max_strips_per_packet: %d\n", packet.max_strips_per_packet) ;
    printf(" pixels_per_strip: %d\n", packet.pixels_per_strip) ;
    printf(" update_period: %d\n", packet.update_period) ;
    printf(" power_total: %d\n", packet.power_total) ;
    printf(" delta_sequence: %d\n", packet.delta_sequence) ;
    printf(" controller_id: %d\n", packet.controller_id) ;
    printf(" group_id: %d\n", packet.group_id) ;
    printf(" artnet_universe: %d\n", packet.artnet_universe) ;
    printf(" artnet_channel: %d\n", packet.artnet_channel) ;
  }

  struct{
    uint8_t mac_address[6];
    uint8_t ip_address[4];
    uint8_t device_type;
    uint8_t protocol_version; // for the device, not the discovery
    uint16_t vendor_id;
    uint16_t product_id;
    uint16_t hw_revision;
    uint16_t sw_revision;
    uint32_t link_speed;
    uint8_t strips_attached;
    uint8_t max_strips_per_packet;
    uint16_t pixels_per_strip;
    uint32_t update_period;
    uint32_t power_total;
    uint32_t delta_sequence;
    uint32_t controller_id;
    uint32_t group_id;
    uint16_t artnet_universe;
    uint16_t artnet_channel;

  } packet;
};


class PixelPusher
{
public:

  PixelPusher() : packet_number(0) {
    memset(&description, 0, sizeof(description));
  }

  void update(const Discovery& disc, const udp::endpoint& from) {
    memcpy(&description.packet, &disc.packet, sizeof(description));
    for(unsigned int i = 0;i < disc.packet.strips_attached;i++) {
      pixels[i].resize(3*disc.packet.pixels_per_strip);

    }
    target = from;
    target.port(9897);
  }

  void send() {
    std::vector<uint8_t> packet;
    asio::io_service io_service;
    udp::socket sock(io_service, udp::endpoint(udp::v4(), 0));

    udp::resolver resolver(io_service);
    udp::endpoint endpoint = *resolver.resolve({udp::v4(),description.ip_address(), "9897"});

    packet.clear();
    packet.push_back((packet_number >> 24) & 0xFF);
    packet.push_back((packet_number >> 16) & 0xFF);
    packet.push_back((packet_number >> 8) & 0xFF);
    packet.push_back(packet_number & 0xFF);
    packet_number++;

    
    for(unsigned int i = 0; i < description.packet.strips_attached;i+=description.packet.max_strips_per_packet) {
      for(unsigned int j = 0;i < description.packet.max_strips_per_packet;i++) {
        unsigned int idx = i + j;
        //mPacket.push_back((stripNumber >> 8) & 0xFF);
        packet.push_back((uint8_t)(idx & 0xFF));

        memset(&pixels[idx][0], 5, pixels[idx].size());
        //printf("pixels: %ld\n", pixels[0].size());
        std::copy(pixels[idx].begin(), pixels[idx].end(), std::back_inserter(packet));
      }
    }

    //printf("sending %d bytes to:\n", packet.size());
    //std::cout << "Sending " << packet.size() << " bytes to " << endpoint << std::endl;
    sock.send_to(asio::buffer(&packet[0],packet.size()), endpoint);
  }

  void print() {
    description.print();
  }

private:
  Discovery description;
  udp::endpoint target;


  std::vector<uint8_t> pixels[8];
  uint32_t packet_number;
};

class DiscoveryService
{
public:
  DiscoveryService(short port)
    : socket_(io_service, udp::endpoint(udp::v4(), port)),
      listener(&DiscoveryService::do_receive, this)
  {  }

  std::map<std::string, std::shared_ptr<PixelPusher>> pushers;
private:

  void do_receive()
  {
    Discovery disc;
    while(true) {
      size_t bytes_recvd = socket_.receive_from(asio::buffer(&disc.packet, sizeof(disc.packet)), sender_endpoint_);
      if (bytes_recvd > 0)
      {
        std::string mac_address = disc.mac_address();
        if (pushers.find(mac_address) == pushers.end()) {
          pushers[mac_address] = std::make_shared<PixelPusher>();
        }
        pushers[mac_address]->update(disc, sender_endpoint_);
        pushers[mac_address]->print();
        printf("\n");
      }
    }
  }

  asio::io_service io_service;

  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  std::thread listener;

};

void diep(const char *s)
{
  perror(s);
  exit(1);
}


int main(void)
{
  DiscoveryService ds(7331);
  //ds.run();
  while(true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000/16));

    std::string mac_address("d8:80:39:65:f1:91");
    if(ds.pushers.find(mac_address) != ds.pushers.end()) {
      std::shared_ptr<PixelPusher> pusher = ds.pushers[mac_address];
      pusher->send();
    }
    // if(pusher != nullptr) {
    //   //pusher->send();
    // }
  }
  // struct sockaddr_in s_client;
  // int i, slen=sizeof(s_client);
  // char buf[BUFLEN];

  // memset((char *) &s_client, 0, sizeof(s_client));
  // s_client.sin_family = AF_INET;
  // s_client.sin_port = htons(9897);
  // s_client.sin_addr = si_other.sin_addr;
  
  // printf("Sending packet %d\n", i);
  // sprintf(buf, "This is packet %d\n", i);
  // if (sendto(s, buf, BUFLEN, 0, (sockaddr*)&s_client, slen)==-1)
  //   diep("sendto()");

  return 0;
}