import java.io.*;  
import java.net.*;  
public class MyServer {  
public static void main(String[] args){  
    try{  
        ServerSocket ss=new ServerSocket(6666);  
        Socket s=ss.accept();//establishes connection   
        DataOutputStream dout=new DataOutputStream(s.getOutputStream());  
        dout.writeUTF("Hello Client From Server");  
        dout.flush();  
        dout.close();  
        ss.close();  
        ProcessBuilder processBuilder = new ProcessBuilder();
        String command = "notepad.exe testing.txt";
 
        Process process = Runtime.getRuntime().exec(command);
    }catch(Exception e){System.out.println(e);}  
}  
}  