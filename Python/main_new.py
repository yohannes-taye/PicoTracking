#!/usr/bin/python
# accessory.py
# License GPLv2
# (c) Manuel Di Cerbo, Nexus-Computing GmbH
 
import usb.core
import usb.util
import struct
import time
import threading
import os
import socket
import debugpy
import socket 
from attribs import *


#PICO NEO 3 pro 
ACCESSORY_VID = 0x18d1
NACCESSORY_VID = 0X2d40
# ACCESSORY_PID = (0xff48, 0xff40)
ACCESSORY_PID = (0x2d01,)
NETLINK_KOBJECT_UEVENT = 15
 

'''
#PICO NEO 3 
ACCESSORY_VID = 0x2d40
NACCESSORY_VID = 0X2d40
# ACCESSORY_PID = (0xff48, 0xff40)
ACCESSORY_PID = (0x00b2,)
NETLINK_KOBJECT_UEVENT = 15
'''

'''Download an image from an
 http address and save it to a global variable '''

def main():
    # debugpy.listen(5678)
    # print("Press play!")
    # debugpy.wait_for_client()
    while True:
        # print("starting accessory task")
        try:
            accessory_task()
            time.sleep(5)
        except ValueError:
            pass; 
            print(f"LALI_DEBUG: No compatible device found")
        # print("accessory task finished")
 
def setup_local_udp_connection():
    global UDPClientSocket
    global serverAddressPort

    msgFromClient       = "Hello UDP Server"
    bytesToSend         = str.encode(msgFromClient)
    serverAddressPort   = ("127.0.0.1", 20001)
    bufferSize          = 1024
    # Create a UDP socket at client side

    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) 

def accessory_task():
    global UDPClientSocket
    global serverAddressPort
    dev = usb.core.find(idVendor=NACCESSORY_VID);
    setup_local_udp_connection()
    if dev is None:
        dev = usb.core.find(idVendor=ACCESSORY_VID);
        if dev is None: 
            print("LALI_DEBUG: RAISE ERROR FROM1")
            raise ValueError("No compatible device not found")
 
    print("LALI_DEBUG: compatible device found")
 
    if dev.idProduct in ACCESSORY_PID:
        print("LALI_DEBUG: device is in accessory mode")

    else:
        print("LALID_DEBUG: device is not in accessory mode yet")
        accessory(dev)
        dev = usb.core.find(idVendor=ACCESSORY_VID);
        if dev is None: 
            dev = usb.core.find(idVendor=NACCESSORY_VID);
            if dev is None:
                print("LALI_DEBUG: RAISE ERROR FROM2")
                raise ValueError("No compatible device not found")
        print(f"Id product: {dev.idProduct}")
        if dev.idProduct in ACCESSORY_PID:
            print("device is in accessory mode")
        else:
            pass
            # raise ValueError("")
    print("HERE2")
    # dev.set_configuration() #TODO: I have made changes here
    # even if the Android device is already in accessory mode
    # setting the configuration will result in the
    # UsbManager starting an "accessory connected" intent
    # and hence a small delay is required before communication
    # works properly
    time.sleep(1)
 
    dev = usb.core.find(idVendor = ACCESSORY_VID)
    print(type(dev))
    cfg = dev.get_active_configuration() #TODO: I have made changes here 
    if_num = cfg[(0,0)].bInterfaceNumber
    intf = usb.util.find_descriptor(cfg, bInterfaceNumber = if_num)
    print("HERE4")
     
    ep_out = usb.util.find_descriptor(
        intf,
        custom_match = \
        lambda e: \
            usb.util.endpoint_direction(e.bEndpointAddress) == \
            usb.util.ENDPOINT_OUT
    )
    print("HERE5")
 
    ep_in = usb.util.find_descriptor(
        intf,
        custom_match = \
        lambda e: \
            usb.util.endpoint_direction(e.bEndpointAddress) == \
            usb.util.ENDPOINT_IN
    )
   
    print("HERE6")
 
    # writer_thread = threading.Thread(target = writer, args = (ep_out, ))
    # writer_thread.start()
    length = -1
    while True:
        try:
            data = ep_in.read(size_or_buffer = 28, timeout = 1000)
            data = bytearray(data)
            UDPClientSocket.sendto(data , serverAddressPort)

            # tx = struct.unpack('>f', data[0:4])
            # ty = struct.unpack('>f', data[4:8])
            #dev tz = struct.unpack('>f', data[8:12])

            # rx = struct.unpack('>f', data[12:16])
            # ry = struct.unpack('>f', data[16:20])
            # rz = struct.unpack('>f', data[20:24])
            # rw = struct.unpack('>f', data[24:28])

            # print(f"position x: {tx}")
            # print(f"position y: {ty}")
            # print(f"position z: {tz}")
            # print(f"rotation x: {rx}")
            # print(f"rotation y: {ry}")
            # print(f"rotation z: {rz}")
            # print(f"rotation w: {rw}")

            # struct.unpack('>f', data)
            # struct.unpack('>f', data)
            # struct.unpack('>f', data)

            print(type(data))
            print(data)


            # print("read value %d" % data[0])
            # print("read value %d" % data[1])
            # print("read value %d" % data[2])
            # print("read value %d" % data[3])
            # print("read value %d" % data[4])
        except usb.core.USBError as e:
            # print("failed to send IN transfer")
            if str(e) == "[Errno 19] No such device (it may have been disconnected)": 
                print(1)

            elif str(e) == "[Errno 110] Operation timed out": 
                print(2)
            else: 
                print(3)

            # print(str(e))
            # print(str(e.backend_error_code))

            dev = usb.core.find(idVendor=NACCESSORY_VID);
            if dev is None:
                # print("LALI_DEBUG: Was not in host mode")
                dev = usb.core.find(idVendor=ACCESSORY_VID);
                if dev is None: 
                    pass 
                    # print("LALI_DEBUG: Cant also find in accessory mode ")
                # break
        except Exception as e:
            print(4) 
                # logging.error(traceback.format_exc())
 
    # writer_thread.join()
    # print("exiting application")
 
def writer (ep_out):
    while True:
        try:
            length = ep_out.write([0], timeout = 0)
            print("%d bytes written" % length)
            time.sleep(0.5)
        except usb.core.USBError:
            print("error in writer thread")
            break
 
 
def accessory(dev):
    version = dev.ctrl_transfer(
                usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_IN,
                51, 0, 0, 2)
 
    print("version is: %d" % struct.unpack('<H',version)) 
 
    assert dev.ctrl_transfer(
            usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_OUT,
            52, 0, 0, MANUFACTURER) == len(MANUFACTURER) 
     
    assert dev.ctrl_transfer(
            usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_OUT,
            52, 0, 1, MODEL_NAME) == len(MODEL_NAME) 
     
     
    assert dev.ctrl_transfer(
            usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_OUT,
            52, 0, 2, DESCRIPTION) == len(DESCRIPTION) 
 
    assert dev.ctrl_transfer(
            usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_OUT,
            52, 0, 3, VERSION) == len(VERSION) 
 
    assert dev.ctrl_transfer(
            usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_OUT,
            52, 0, 4, URL) == len(URL) 
 
    assert dev.ctrl_transfer(
            usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_OUT,
            52, 0, 5, SERIAL_NUMBER) == len(SERIAL_NUMBER)
     
    dev.ctrl_transfer(
            usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_OUT,
            53, 0, 0, None)
    print("HERE11")
    time.sleep(1)
 
if __name__ == "__main__":
    main()