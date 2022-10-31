import configparser
import subprocess
import time 
import debugpy 
import subprocess as sp 


driver_script_running = False 
extProc = None 
"""execute command line and read response from stdout"""
def execute(cmd):
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    return iter(p.stdout.readline, b'')

def get_device_list(): 
    device = [] 
    for path in execute("lsusb"):
        path = str(path)
        
        #Get index of the word "ID" in path 
        # and get the next 10 characters after that 
        # which is the ID of the device
        deviceID = path[path.index("ID") + 3 : path.index("ID") + 12]
        device.append(deviceID)
    return device

"""Read settings.ini file and return a dictionary of the settings using configparser"""
def read_settings():
    print("Reading settings.ini file")
    global config 
    config = configparser.ConfigParser()
    config.read('settings.ini')
    time_out = config["pico"]["device_detect_timeout"]
    pico_host_mode_device_id = config["pico"]["pico_host_mode_device_id"]
    pico_accessory_mode_device_id = config["pico"]["pico_accessory_mode_device_id"]
    print("time_out: ", time_out)
    print("pico_host_mode_device_id: ", pico_host_mode_device_id)
    print("pico_accessory_mode_device_id: ", pico_accessory_mode_device_id)
    

def run_driver_script(run): 
    global extProc
    global driver_script_running
    global config
    if not driver_script_running and run: 
        print("Running driver script")
        extProc = sp.Popen([config["pico"]["python_path"],'main_new.py']) # runs main_new.py 
        driver_script_running = True
        # sp.Popen.terminate(extProc) # closes the process
    elif run == False and extProc : 
        print("Terminating driver script")

        sp.Popen.terminate(extProc)
        extProc = None 
        driver_script_running = False

def run(time_out, pico_host_mode_device_id, pico_accessory_mode_device_id): 
    # call function every 5 seconds
    while True:
        
        deviceList = get_device_list()
        
        if deviceList.count(pico_host_mode_device_id) == 0 and deviceList.count(pico_accessory_mode_device_id) == 0:
            print("Device not found")
            # call function again in 5 seconds
            run_driver_script(False)
            time.sleep(time_out)
        else:
            print("Device found")
            # call function again in 5 seconds
            time.sleep(time_out)
            run_driver_script(True)


# debugpy.listen(5678)
# print("Press play!")
# debugpy.wait_for_client()

"""main function"""
if __name__ == "__main__":
    global config 
    read_settings()
    time_out = config["pico"]["device_detect_timeout"]
    pico_host_mode_device_id = config["pico"]["pico_host_mode_device_id"]
    pico_accessory_mode_device_id = config["pico"]["pico_accessory_mode_device_id"]

    run(int(time_out), pico_host_mode_device_id, pico_accessory_mode_device_id)    

    