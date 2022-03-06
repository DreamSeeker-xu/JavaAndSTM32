package com.xu.javaFx.controller;


import com.xu.javaFx.entity.ClientNum;
import com.xu.javaFx.utils.Byte_Hex;
import com.xu.javaFx.utils.ClassUtils;
import com.xu.javaFx.utils.ListUtil;
import com.xu.javaFx.utils.ServerUtils;
import de.felixroske.jfxsupport.FXMLController;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextArea;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.util.*;


/**
 * Creat by xu on 2022/01/03 20:27
 */
@FXMLController
public class ServerController implements Initializable {

    @FXML
    private TextArea rece_area;

    @FXML
    private TextArea send_area;

    @FXML
    private Button clear_rece;

    @FXML
    private Button clear_send;

    @FXML
    private ListView<String> client_list;

    @FXML
    private Label client_num;

    private int client_count = 0;
    @FXML
    private TextArea server_mess;
    //存放客户端
    public static Map<Integer,Socket> clientMap;

    private Socket socket;

    private InputStream ins;

    private BufferedReader buffreader;

    private  OutputStream ous;

    private long lasttime;

    @FXML
    void ClearReceClick(ActionEvent event) {
        rece_area.setText("");
    }

    @FXML
    void ClearSendClick(ActionEvent event) {
        send_area.setText("");
    }
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        //设置接收框不可编辑
        rece_area.setEditable(false);
        //设置发送框不可编辑
        send_area.setEditable(false);

        rece_area.setPrefRowCount(10);
        //设置发送框自动换行
        send_area.setWrapText(true);
        //设置接收框自动换行
        rece_area.setWrapText(true);
        server_mess.setEditable(false);
        server_mess.setWrapText(true);
        //创建map集合接收客户端
        clientMap = new HashMap<Integer,Socket>();
        //创建一个新的线程等待客户端的连接
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    //初始化服务Socket端口
                    ServerSocket serverSocket = new ServerSocket(5001);
                    server_mess.appendText("服务器初始化成功，等待客户端连接\r\n");
                    while (true) {
                        try {
                            //等待客户端连接
                            socket = serverSocket.accept();
                            System.out.println("1111");
                            //设置Socket超时时间
                            socket.setSoTimeout(10000);
                            //获取数据输入流
                            buffreader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                            //读取客户端的第一条信息(判断为客户端还是设备)
                            String clientname = buffreader.readLine();
                            System.out.println(clientname);
                            int clientid = 0;
                            //获取客户端id
                            if ((clientid = ServerUtils.SetClientid(clientMap, clientname)) != 0) {
                                //将当前客户端放入集合
                                clientMap.put(clientid, socket);
                                //获取连接客户端IP
                                String ipaddr = socket.getInetAddress().getHostAddress();
                                //将客户端信息放入列表
                                Platform.runLater(() -> {
                                    ListUtil.AddData(client_list, ipaddr);
                                    client_count += 1;
                                    client_num.setText(String.valueOf(client_count));
                                });
                                server_mess.appendText("客户端" + ipaddr + "已上线" + "id=" + clientid + "\r\n");
                                //为客户端创建一个新的线程
                                ServerThread serverThread = new ServerThread(socket);
                                //开启新的线程
                                serverThread.start();
                            } else
                                throw new IOException();
                    }catch(Exception e){
                         System.out.println("当前不是合法客户端");
                        if (buffreader != null)
                            buffreader.close();
                        if (socket != null)
                            socket.close();
                        e.printStackTrace();
                    }
                }
                } catch (IOException e) {
                    server_mess.appendText("服务器初始化失败，请检查是否占用5000端口\r\n");
                }
            }
        });
        thread.start();
    }
    private void ClientDisContent(Socket socket){
        Platform.runLater(()->{
            clientMap.remove(socket);
            client_count -= 1;
            client_num.setText(String.valueOf(client_count));
            ListUtil.DelData(client_list,socket.getInetAddress().getHostAddress());
            server_mess.appendText("客户端" + socket.getInetAddress().getHostAddress() + "断开连接\r\n");
        });

    }

    private  boolean MoveFromMap(Socket socket){
        boolean moveflag = false;
        int count = 0;
        for(Integer id : clientMap.keySet()){
            Socket exitsocket = clientMap.get(id);
            if(socket.equals(exitsocket)){
                clientMap.remove(id);
                moveflag = true;
                break;
            }
            count++;
        }
        if(count == clientMap.size()){
            moveflag = false;
        }
        return moveflag;
    }
    class ServerThread extends Thread{

        private boolean connect = false;

        private Socket socket;

        private InputStream ins;

        private  OutputStream ous;

        public ServerThread(Socket socket){
            this.socket = socket;
            try {
                //创建输入流
                ins = socket.getInputStream();
                //创建输出流
                ous = socket.getOutputStream();
                //设置连接状态
                connect = true;
            } catch (IOException e) {
                if(MoveFromMap(socket))
                    System.out.println("客户端删除成功");
                ClientDisContent(socket);
                connect  = false;
                try {
                    if(ins != null){
                        ins.close();
                    }
                    if(buffreader != null){
                        buffreader.close();
                    }
                    if(ous != null){
                        ous.close();
                    }
                    if(socket != null){
                        socket.close();
                    }
                }catch (IOException ioe) {
                    ioe.printStackTrace();
                }
            }
        }
        @Override
        public void run() {
                try {
                    while (connect) {ServerUtils.ReceiveFormClient(clientMap, ins, ous, rece_area, send_area, socket);
                    }

                } catch (IOException e) {
                    if(MoveFromMap(socket))
                        System.out.println("客户端删除成功");
                    //ClientDisContent(socket);
                    connect = false;
                    try {
                        if(ins != null){
                            ins.close();
                        }
                        if(buffreader != null){
                            buffreader.close();
                        }
                        if(ous != null){
                            ous.close();
                        }
                        if(socket != null){
                            socket.close();
                        }
                    }catch (IOException ioe) {

                    }
                }finally {
                    if(MoveFromMap(socket))
                        System.out.println("客户端删除成功");
                     ClientDisContent(socket);
                    connect = false;
                    try {
                        if(ins != null){
                            ins.close();

                        }
                        if(buffreader != null){
                            buffreader.close();
                        }
                        if(ous != null){
                            ous.close();
                        }
                        if(socket != null){
                            socket.close();
                        }
                    }catch (IOException ioe) {
                    }
                }
        }

    }
}