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
    //TODO: change the return value to be an array of ints to 
    // indicate the multiple possible faliure points. 
    @Keep
    public String attachAccessory() {
        if(this.context == null){
            return "ERROR: Context is null"; 
        }
        UsbAccessory accessory = getAccessory_new(); 
        UsbManager mUsbManager = (UsbManager) this.context.getSystemService(Context.USB_SERVICE);
        final ParcelFileDescriptor parcelFileDescriptor;
        if(accessory != null){
            parcelFileDescriptor = mUsbManager.openAccessory(accessory);
        }else{
            return "ERROR: getAccessory returned null"; 
        }

        if (parcelFileDescriptor != null) {
            final FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();
            this.mOutputStream = new FileOutputStream(fileDescriptor);
            this.mInputStream = new FileInputStream(fileDescriptor);
            return "Success"; 
          
            
        }else{
            return "ERROR: ParcelFileDescriptor returned null"; 
        }
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