package com.xu.javaFx.utils;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import javafx.scene.control.ListView;

/**
 * Creat by xu on 2022/01/07 19:10
 */
public class ListUtil {
    private static ObservableList observableList;

    static {
        observableList = FXCollections.observableArrayList();
    }

    /***
     * 添加客户端到列表
     * @param listView
     * @param str
     */
    public static void AddData(ListView listView, String str){
        //ObservableList<String> observableList = FXCollections.observableArrayList();
        observableList.add(str);
        listView.setItems(observableList);
    }

    /***
     * 客户端从列表删除
     * @param listView
     * @param str
     */
    public static void DelData(ListView listView,String str){
        int datasize = listView.getItems().size();
        for(int i = 0;i < datasize;i++){
            String client  = (String) listView.getItems().get(i);
            if(client.equals(str)){
                listView.getItems().remove(i);
                break;
            }
        }
    }
}
