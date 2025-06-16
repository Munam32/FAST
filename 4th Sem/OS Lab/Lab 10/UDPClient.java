// import java.net.*;
// import java.io.*;

// public class UDPClient {
//     public static void main(String[] args) throws Exception {
//         DatagramSocket socket = new DatagramSocket();
//         BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

//         System.out.print("Enter message to send to server: ");
//         String message = input.readLine();

//         byte[] buffer = message.getBytes();
//         InetAddress address = InetAddress.getByName("localhost");
//         DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, 6000);

//         socket.send(packet);

//         byte[] response = new byte[1024];
//         DatagramPacket responsePacket = new DatagramPacket(response, response.length);
//         socket.receive(responsePacket);

//         String reply = new String(responsePacket.getData(), 0, responsePacket.getLength());
//         System.out.println("Server replied: " + reply);

//         socket.close();
//     }
// }

import java.net.*;
import java.io.*;

public class UDPClient {
    public static void main(String[] args) throws Exception {
        DatagramSocket socket = new DatagramSocket();
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));

        System.out.print("Enter message to send to server (e.g., TIME): ");
        String message = input.readLine();

        byte[] buffer = message.getBytes();
        InetAddress address = InetAddress.getByName("localhost");
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, 6000);

        socket.send(packet);

        byte[] response = new byte[1024];
        DatagramPacket responsePacket = new DatagramPacket(response, response.length);
        socket.receive(responsePacket);

        String reply = new String(responsePacket.getData(), 0, responsePacket.getLength());
        System.out.println("Server replied: " + reply);

        socket.close();
    }
}