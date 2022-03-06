package com.xu.javaFx.utils;




import com.xu.javaFx.entity.ClientNum;

import javafx.application.Platform;
import javafx.scene.control.TextArea;


import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.concurrent.*;

/**
 * Creat by xu on 2022/01/08 09:25
 */
public class ServerUtils {
    private static long lasttime;
    private static String str = null;
    private static int rowcount = 0;
    /***
     * 为客户端随机生成id
     * @param clientmap
     * @param clientname
     * @return
     * @throws IOException
     */
    public static int SetClientid(Map<Integer,Socket> clientmap,String clientname) throws IOException{
        int clientid = 0;
        Random random = new Random();
        while (true){
                if(clientname == null)
                    return 0;
                if(clientname.equals("client")){
                    clientid = random.nextInt((ClientNum.CLIENT_MAX + 1)- ClientNum.CLIENT_MIN) + ClientNum.CLIENT_MIN;
                }else if(clientname.equals("devide")){
                    clientid = random.nextInt((ClientNum.DEVIDE_MAX + 1) - ClientNum.DEVIDE_MIN) + ClientNum.DEVIDE_MIN;
                }else {
                    return 0;
                }
                if(clientmap == null)
                    break;
                if(!clientmap.containsKey(clientid)) {
                    break;
                }
            }
        return clientid;
    }


    /***
     *
     * @param clientmap
     * @param sendarea
     * @return
     */
    public static boolean SendToClient(Map<Integer,Socket> clientmap,TextArea sendarea,String str,Socket socket){
        boolean sendflag = false;
        OutputStream ous = null;
        try {
            String ipaddr = socket.getInetAddress().getHostAddress();
            ous = socket.getOutputStream();
            ous.write(Byte_Hex.hexStringToByteArray(str));
            ous.flush();
            SimpleDateFormat simpleDateFormat= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            String nowtime = simpleDateFormat.format(new Date());
            Platform.runLater(()->{
                sendarea.appendText(nowtime + "\r\n");
                sendarea.appendText(ipaddr + ":" + str + "\r\n");
            });
            sendflag = true;
        } catch (IOException e) {
            System.out.println("服务器发送信息失败");
            sendflag = false;
        }
        return sendflag;
    }

    /***
     * 接收客户端发送来的信息
     * @param clientmap
     * @param ins
     * @param recearea
     * @throws IOException
     */
    public static void ReceiveFormClient(Map<Integer,Socket> clientmap, InputStream ins, OutputStream ous, TextArea recearea, TextArea sendarea, Socket socket)throws IOException {
        int len = 0;
        byte[] readbuffer = new byte[1];
        String str = "";

        String[] strs = null;
        lasttime = System.currentTimeMillis();
        //获取客户端ip
        String ipaddr = socket.getInetAddress().getHostAddress();
        //数据没有接收完毕
        while ((len = ins.read(readbuffer)) != -1) {
            //将接收到的字节转换为字符串并合并
            str += Byte_Hex.bytesToHexString(readbuffer) + " ";
            strs = str.split(" ");
            //System.out.println("接收" + str);
            //接收一帧数据
            if (strs[strs.length - 1].equals("CF") || strs[strs.length - 1].equals("DF")) {
                ServerUtils.str = str;
                Platform.runLater(()->{
                    SimpleDateFormat simpleDateFormat= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
                    String nowtime = simpleDateFormat.format(new Date());
                    recearea.appendText(nowtime + "\r\n");
                    recearea.appendText(ipaddr + ":" + ServerUtils.str + "\r\n");
                    rowcount++;
                });
                //System.out.println(str);
                int endindex = Byte_Hex.hexStrToInt(strs[2]) + 3;
                //ESP8266发来的信息
                if (strs[0].equals("FD") && strs[endindex].equals("DF")) {
                    //遍历每个客户端
                    for (Integer id : clientmap.keySet()) {
                        //获取客户端Socket
                        Socket existsocket = clientmap.get(id);
                        if (id >= ClientNum.CLIENT_MIN && id <= ClientNum.CLIENT_MAX && existsocket != socket) {
                            if (SendToClient(clientmap, sendarea, str, existsocket)) {
                                System.out.println("服务器发送成功");
                            } else {
                                throw new IOException();
                            }
                        }
                    }
                } else if (strs[0].equals("FC") && strs[endindex].equals("CF")) {
                    for (Integer id : clientmap.keySet()) {
                        Socket exitsocket = clientmap.get(id);
                        //发送给设备
                        if (id >= ClientNum.DEVIDE_MIN && id <= ClientNum.DEVIDE_MAX && exitsocket != socket) {
                            if (SendToClient(clientmap, sendarea, str, exitsocket)) {
                                System.out.println("服务器发送成功");
                            } else {
                                System.out.println("服务器发送失败");
                                throw new IOException();
                            }
                        }
                    }
                }
                str = "";
                System.out.println("接收到数据");
            }
            lasttime = System.currentTimeMillis();
        }
        System.out.println("接收完毕");
        throw new IOException();
    }
}
