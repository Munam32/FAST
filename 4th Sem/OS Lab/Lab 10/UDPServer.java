// import java.net.*;

// public class UDPServer {
//     public static void main(String[] args) throws Exception {
//         DatagramSocket socket = new DatagramSocket(6000);
//         byte[] buffer = new byte[1024];

//         DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
//         System.out.println("Waiting for client message...");
//         socket.receive(packet);

//         String message = new String(packet.getData(), 0, packet.getLength());
//         System.out.println("Client says: " + message);

//         String response = "Message received: " + message;
//         byte[] responseBytes = response.getBytes();

//         InetAddress clientAddress = packet.getAddress();
//         int clientPort = packet.getPort();

//         DatagramPacket responsePacket = new DatagramPacket(responseBytes, responseBytes.length, clientAddress, clientPort);
//         socket.send(responsePacket);

//         socket.close();
//     }
// }

import java.net.*;
import java.time.LocalDateTime;

public class UDPServer {
    public static void main(String[] args) throws Exception {
        DatagramSocket socket = new DatagramSocket(6000);
        byte[] buffer = new byte[1024];

        System.out.println("UDP Time Server is running...");

        try {
            while (true) {
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                socket.receive(packet);

                String message = new String(packet.getData(), 0, packet.getLength());
                System.out.println("Received from client: " + message);

                String response;
                if (message.equals("TIME")) {
                    response = LocalDateTime.now().toString();
                } else {
                    response = "INVALID REQUEST";
                }

                byte[] responseBytes = response.getBytes();
                InetAddress clientAddress = packet.getAddress();
                int clientPort = packet.getPort();

                DatagramPacket responsePacket = new DatagramPacket(responseBytes, responseBytes.length, clientAddress, clientPort);
                socket.send(responsePacket);
            }
        } finally {
            socket.close();
        }
    }
}