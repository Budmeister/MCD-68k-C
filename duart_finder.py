import serial

if __name__ == "__main__":
    bauds = [
            50,
            75,
            110,
            150,
            200,
            300,
            600,
            1200,
            1050,
            1800,
            2000,
            2400,
            3600,
            4800,
            7200,
            9600,
            14400,
            19200,
            28800,
            38400,
            57600,
            115200
    ]

    good_bauds = {}

    for baud in bauds:
        s = serial.Serial("COM4", baudrate=baud)
        s.timeout = 2
        line = str(s.read(20))
        for c in line:
            if c in "Hello World":
                if baud in good_bauds:
                    good_bauds[baud].add(c)
                else:
                    good_bauds[baud] = {c}
                print(f"Good baud found: {baud}, character: {c}")
        s.close()
    print(f"Good bauds found: {good_bauds}")
