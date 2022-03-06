package com.xu.javaFx.utils;

import java.lang.reflect.Field;
import java.lang.reflect.Method;

/**
 * Creat by xu on 2022/01/11 13:22
 */
public class ClassUtils {
    public static boolean SetClassProperty(Object o,String[] strs){
        //根据当前对象获取类
        Class c = o.getClass();
        //获取当前类中的所有属性
        Field[] fields = c.getDeclaredFields();
        int i = 0;
        //遍历每个属性
        for(Field f : fields){
            //System.out.println(f.getName());
            if((!f.getName().equals("startflag")) && (!f.getName().equals("endflag"))){
                try {
                    f.setAccessible(true);
                    f.set(o,Byte_Hex.hexStrToInt(strs[i]));
                } catch (Exception e) {
                    System.out.println("设置对象属性失败");
                    e.printStackTrace();
                    return false;
                }
            }
            i++;
        }
        return true;
    }
    /***
     * 获取当前对象所有属性值
     * @param o
     * @return
     */
    public static int[] GetClassProperty(Object o){
        //根据当前对象获取类
        Class c = o.getClass();
        //获取当前类中的所有属性个数
        int len = c.getDeclaredFields().length;
        //获取当前类中的所有属性
        Field[] fields = c.getDeclaredFields();
        int ints[] = new int[len];
        int i = 0;
        //遍历每个属性
        for(Field f : fields){
            try {
                //获取到每个属性的get方法
                Method method = c.getMethod("get" + getMethodName(f.getName()));
                //执行获取到的get方法，获取当前对象的每个属性值
                ints[i] = (int) method.invoke(o);
                i++;

            } catch (Exception e) {
                System.out.println("获取当前对象属性失败");
                ints = null;
            }
        }
        return ints;
    }
    private static String getMethodName(String fildeName) throws Exception{
        byte[] items = fildeName.getBytes();
        items[0] = (byte) ((char)items[0] - 'a' + 'A');
        return new String(items);
    }
}
