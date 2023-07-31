In the terminal:

    sudo apt install build-essential gcc make cmake cmake-gui cmake-curses-gui
    sudo apt install fakeroot devscripts dh-make lsb-release
    sudo apt install libbluetooth-dev
    sudo apt install libssl-dev
    sudo apt install doxygen graphviz

In gattlib folder:

    mkdir -p build && cd build
    cmake -DGATTLIB_BUILD_EXAMPLES=NO -DGATTLIB_SHARED_LIB=NO -DGATTLIB_BUILD_DOCS=NO -DGATTLIB_PYTHON_INTERFACE=NO ..
    make
    sudo make install

In MQTT folder:

    mkdir -p build && cd build
    cmake -DPAHO_BUILD_SHARED=TRUE -DPAHO_BUILD_STATIC=TRUE -DPAHO_ENABLE_TESTING=FALSE -DPAHO_BUILD_SAMPLES=FALSE ..
    make
    sudo make install

In jbdtools folder:

    make
    sudo make install

In the terminal:

    sudo ldconfig

Check which usb port its connected to:

    dmesg | grep ttyUSB

Go to the jbdtool folder (It takes sometime before a response is printed):

    sudo ./jbdtool -t serial:/dev/ttyUSB0
