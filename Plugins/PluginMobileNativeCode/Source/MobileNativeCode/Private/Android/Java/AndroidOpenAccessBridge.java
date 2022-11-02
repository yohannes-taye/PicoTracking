package com.Plugins.MobileNativeCode;//Use only this package, do not change it!!!

import android.support.annotation.Keep;
import android.hardware.usb.UsbAccessory;
import android.hardware.usb.UsbManager;

import android.content.Context;
import android.app.Activity;
import android.os.ParcelFileDescriptor;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;


@Keep
public class AndroidOpenAccessBridge {
    @Keep 
    String globalVariable = "Value not changed."; 
    @Keep
    Context context; 

    @Keep
    FileOutputStream mOutputStream;

    @Keep
    FileInputStream mInputStream;

    @Keep
    boolean attempting_to_attach = false;
    
    //Calling *.cpp code
    @Keep
    public static native void CallBackCppAndroid(String returnStr);
    
    
    AndroidOpenAccessBridge(){
        this.context = null; 
    }
    AndroidOpenAccessBridge(Activity activity){
        this.context = activity;
    }
    
    @Keep 
    public String testLocalFunction(final String test){
        this.globalVariable = "Value after change by local function"; 
        return this.globalVariable; 
    }
    @Keep 
    public String getLocalVariable(){
        return globalVariable;
    }

    @Keep
    public static AndroidOpenAccessBridge getAndroidOpenAccessBrigeInstance(Activity activity) {
        return new AndroidOpenAccessBridge(activity); 
    }


    @Keep
    public static String detectAccessory(final Activity activity) {
        try{
            Context context = activity; 
            UsbManager mUsbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
            final UsbAccessory[] accessoryList = mUsbManager.getAccessoryList();
            if (accessoryList != null && accessoryList.length > 0) {
                return "YES";
            }
            return "No accessory detected";
        }catch(Exception e){
            return "Error: " + e.toString(); 
        }
    }

    @Keep
    public static boolean detectAccessory_New(final Activity activity) {
        try{
            Context context = activity; 
            UsbManager mUsbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
            final UsbAccessory[] accessoryList = mUsbManager.getAccessoryList();
            if (accessoryList != null && accessoryList.length > 0) {
                return true;
            }
            return false;
        }catch(Exception e){
            return false; 
        }
    }

    @Keep
    public static UsbAccessory getAccessory(final Activity activity) {
        try{
            Context context = activity; 
            UsbManager mUsbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
            final UsbAccessory[] accessoryList = mUsbManager.getAccessoryList();
            if (accessoryList != null && accessoryList.length > 0) {
                return accessoryList[0];
            }
            return null;
        }catch(Exception e){
            return null; 
        }
    }
    @Keep
    public UsbAccessory getAccessory_new() {
        try{
            UsbManager mUsbManager = (UsbManager) this.context.getSystemService(Context.USB_SERVICE);
            final UsbAccessory[] accessoryList = mUsbManager.getAccessoryList();
            if (accessoryList != null && accessoryList.length > 0) {
                return accessoryList[0];
            }
            return null;
        }catch(Exception e){
            return null; 
        }
    }

    @Keep
    private static String maybeAttachAccessory(final Activity activity) {
        UsbAccessory accessory = getAccessory(activity); 
        Context context = activity; 
        UsbManager mUsbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
        final ParcelFileDescriptor parcelFileDescriptor;
        if(accessory != null){
            parcelFileDescriptor = mUsbManager.openAccessory(accessory);
        }else{
            return "ERROR: getAccessory returned null"; 
        }

        if (parcelFileDescriptor != null) {
            final FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();
            FileOutputStream mOutputStream = new FileOutputStream(fileDescriptor);
            FileInputStream mInputStream = new FileInputStream(fileDescriptor);

            char a = 'b';
            byte[] buffer = new byte[5];
            buffer[0] = (byte)a;
            buffer[1] = (byte)a;
            buffer[2] = (byte)a;
            buffer[3] = (byte)a;
            buffer[4] = (byte)a;
            try{
                mOutputStream.write(buffer);
            }catch (IOException e){
                return "ERROR: While attempting to write to stream"; 
            }
            return "Sending to stream";
            
        }else{
            return "ERROR: ParcelFileDescriptor returned null"; 
        }
    }
    //TODO: change the return value to be void 
    // indicate the multiple possible faliure points. 
    @Keep
    public void attachAccessory() {
      //create a new Thread 
        if(attempting_to_attach){
            return; 
        }
        else{
            attempting_to_attach = true; 
            Thread thread = new Thread(new Runnable(){
                @Override
                public void run() {
                    if(AndroidOpenAccessBridge.this.context == null){
                        AndroidOpenAccessBridge.this.attempting_to_attach = false;
                        CallBackCppAndroid("ERROR: Context is null");
            //             return "ERROR: Context is null"; 
                        return; 
                    }
                    UsbAccessory accessory = getAccessory_new(); 
                    UsbManager mUsbManager = (UsbManager) AndroidOpenAccessBridge.this.context.getSystemService(Context.USB_SERVICE);
                    final ParcelFileDescriptor parcelFileDescriptor;
                    if(accessory != null){
                        parcelFileDescriptor = mUsbManager.openAccessory(accessory);
                    }else{
                        AndroidOpenAccessBridge.this.attempting_to_attach = false;
                        CallBackCppAndroid("ERROR: getAccessory returned null");
                        return;
            //             return "ERROR: getAccessory returned null"; 
                    }
                    if (parcelFileDescriptor != null) {
                        final FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();
                        AndroidOpenAccessBridge.this.mOutputStream = new FileOutputStream(fileDescriptor);
                //             this.mInputStream = new FileInputStream(fileDescriptor);
                        AndroidOpenAccessBridge.this.attempting_to_attach = false;
                        CallBackCppAndroid("SUCCESS: Accessory attached");
                        return; 
            //             return "Success"; 
                    }else{
                        AndroidOpenAccessBridge.this.attempting_to_attach = false;
                        CallBackCppAndroid("ERROR: ParcelFileDescriptor returned null");
                        return; 
            //             return "ERROR: ParcelFileDescriptor returned null"; 
                    }               
                }
            });
            thread.start();            
        }
        
        
    }
    
    @Keep
    public byte[] prepareArray(float tx, float ty, float tz, float rx, float ry, float rz, float rw){
        byte[] buffer = new byte[28];
        float[] data = {tx, ty, tz, rx, ry, rz, rw}; 
        int j =0;
        for(int i = 0; i < 28; i += 4){
            int intBits = Float.floatToIntBits(data[j]);
            buffer[i + 0] = (byte) (intBits >> 24);
            buffer[i + 1] = (byte) (intBits >> 16);
            buffer[i + 2] = (byte) (intBits >> 8);
            buffer[i + 3] = (byte) (intBits); 
            j=j+1;
        }
        return buffer;
    }
    @Keep 
    public String sendTrackingData(float tx, float ty, float tz, float rx, float ry, float rz, float rw){
        try{
            byte[] buffer = prepareArray( tx, ty, tz, rx, ry, rz, rw);
            mOutputStream.write(buffer);
        }catch (IOException e){
            return e.getMessage(); 
                // return "ERROR: While attempting to write to stream"; 
        }
        return "Success";
//         return true;  
}
    
    @Keep
    public boolean sendByte(int a){
        byte[] buffer = new byte[5];
        buffer[0] = (byte)(a);
        buffer[1] = (byte)(a + 1);
        buffer[2] = (byte)(a + 2);
        buffer[3] = (byte)(a + 3);
        buffer[4] = (byte)(a + 4);
        try{
            mOutputStream.write(buffer);
        }catch (IOException e){
            return false; 
            // return "ERROR: While attempting to write to stream"; 
        }
        return true; 
        // return "Sending to stream";
    }
}