import java.io.*;
import java.net.*;

public class TCPClient {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 5000);

        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter output = new PrintWriter(socket.getOutputStream(), true);
        BufferedReader serverInput = new BufferedReader(new InputStreamReader(socket.getInputStream()));

        System.out.print("Enter message for server: ");
        String message = input.readLine();
        output.println(message);

        String response = serverInput.readLine();
        System.out.println("Server replied: " + response);

        socket.close();
    }
}