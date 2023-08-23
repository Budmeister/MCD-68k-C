import serial
import random
import time

# Serial port settings
SERIAL_PORT = 'COM3'  # Change this to your serial port
BAUD_RATE = 14400

def generate_random_list(length):
    return [random.randint(1, 2 ** 31 - 1) for _ in range(length)]

def run_test(ser, DELAY, random_list):

    # Send "run" command to the device
    ser.write("run\r".encode())
    time.sleep(DELAY)

    # Send list length to the device
    list_length = len(random_list)
    ser.write(f"{list_length}\r".encode())
    time.sleep(DELAY)

    # Send the list of numbers
    for num in random_list:
        ser.write(f"{num}\r".encode())
        time.sleep(DELAY)

    # Bud
    # Wait for 's' to be received
    while True:
        response = ser.read().decode()
        if response == 's':
            start_time = time.time()
            break

    # Wait for 'e' to be received
    while True:
        response = ser.read().decode()
        if response == 'e':
            end_time = time.time()
            break
    
    bud_sorted_list = ser.readline()
    bud_elapsed_time = end_time - start_time

    # C
    # Wait for 's' to be received
    while True:
        response = ser.read().decode()
        if response == 's':
            start_time = time.time()
            break

    # Wait for 'e' to be received
    while True:
        response = ser.read().decode()
        if response == 'e':
            end_time = time.time()
            break
    
    c_sorted_list = ser.readline()
    c_elapsed_time = end_time - start_time

    return bud_sorted_list, bud_elapsed_time, c_sorted_list, c_elapsed_time

def main():
    # Connect to the serial device
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    DELAY = 0.05

    try:
        # Generate a random list of numbers
        list_length = 1000
        random_list = generate_random_list(list_length)
        print("Original list:", random_list)

        bud_sorted_list, bud_elapsed_time, c_sorted_list, c_elapsed_time = run_test(ser, DELAY, random_list)

        random_list.sort()
        print("Sorted list:", random_list)
        print()

        # Receive the sorted list from the device
        bud_sorted_list = bud_sorted_list.decode().strip()
        bud_sorted_list = list(map(int, bud_sorted_list.split()))

        # Receive the sorted list from the device
        c_sorted_list = c_sorted_list.decode().strip()
        c_sorted_list = list(map(int, c_sorted_list.split()))

        print("Bud produced sorted list:", bud_sorted_list)
        print(f"Bud time: {bud_elapsed_time}s")
        print("Bud's accuracy:", "Correct" if bud_sorted_list == random_list else "Incorrect")
        print()
        print("C produced list:", c_sorted_list)
        print(f"C time: {c_elapsed_time}s")
        print("C's accuracy:", "Correct" if bud_sorted_list == random_list else "Incorrect")



    except Exception as e:
        print("Error:", e)

    finally:
        ser.close()

if __name__ == "__main__":
    main()
