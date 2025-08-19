// import java.io.*;
// import java.net.*;

// public class TCPServer {
//     public static void main(String[] args) throws IOException {
//         ServerSocket serverSocket = new ServerSocket(5000);
//         System.out.println("Server is running and waiting for a client...");

//         Socket socket = serverSocket.accept();
//         System.out.println("Client connected.");

//         BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//         PrintWriter output = new PrintWriter(socket.getOutputStream(), true);

//         String message = input.readLine();
//         System.out.println("Received from client: " + message);

//         output.println("Hello Client, I received your message: " + message);

//         socket.close();
//         serverSocket.close();
//     }
// }

import java.io.*;
import java.net.*;

public class TCPServer {
    
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Server is running and waiting for clients...");

        try {
            while (true) {
                Socket socket = serverSocket.accept();
                System.out.println("New client connected: " + socket.getInetAddress().getHostAddress());

                // Create a new thread to handle the client
                ClientHandler clientHandler = new ClientHandler(socket);
                new Thread(clientHandler).start();
            }
        } finally {
            serverSocket.close();
        }
    }
}

// Class to handle each client in a separate thread
class ClientHandler implements Runnable {
    private Socket socket;

    public ClientHandler(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {
        try (
            BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter output = new PrintWriter(socket.getOutputStream(), true)
        ) {
            String message = input.readLine();
            System.out.println("Received from client (" + socket.getInetAddress().getHostAddress() + "): " + message);

            // Send confirmation message back to the client
            output.println("Server received your message: " + message);
        } catch (IOException e) {
            System.err.println("Error handling client: " + e.getMessage());
        } finally {
            try {
                socket.close();
                System.out.println("Connection closed for client: " + socket.getInetAddress().getHostAddress());
            } catch (IOException e) {
                System.err.println("Error closing socket: " + e.getMessage());
            }
        }
    }
}