import sys
import serial

from PySide2 import QtWidgets
from PySide2.QtGui import QFont

class ApplicationWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self._main = QtWidgets.QWidget()
        self.setCentralWidget(self._main)
        self.setWindowTitle("Car Controller")
        self.layout = QtWidgets.QGridLayout(self._main)

        # Car Parameteres
        self.ser = serial.Serial()
        self.direction = "S"
        self.speed = "9"

        # Intialize communication
        self.commInit()

        # Create widgets
        self.moveForward = QtWidgets.QPushButton('Forward', self._main)
        self.moveForward.setFont(QFont('Arial', 13))
        self.moveForward.clicked.connect(self.on_click_fwd)

        self.moveBackward = QtWidgets.QPushButton('Backward', self._main)
        self.moveBackward.setFont(QFont('Arial', 13))
        self.moveBackward.clicked.connect(self.on_click_bwd)
        
        self.moveRight = QtWidgets.QPushButton('Right', self._main)
        self.moveRight.setFont(QFont('Arial', 13))
        self.moveRight.clicked.connect(self.on_click_right)
        
        self.moveLeft = QtWidgets.QPushButton('Left', self._main)
        self.moveLeft.setFont(QFont('Arial', 13))
        self.moveLeft.clicked.connect(self.on_click_left)
        
        self.Stop = QtWidgets.QPushButton('Stop', self._main)
        self.Stop.setFont(QFont('Arial', 13))
        self.Stop.clicked.connect(self.on_click_stop)

        self.label1 = QtWidgets.QLabel(self._main)
        self.label1.setText("Disconnect")
        self.label1.setFont(QFont('Arial', 13)) 
        
        self.label2 = QtWidgets.QLabel(self._main)
        self.label2.setText("Enter The car speed from 0 to 100")
        self.label2.setFont(QFont('Arial', 13)) 

        self.textBox = QtWidgets.QLineEdit(self._main)        
        self.textBox.setFont(QFont('Arial', 13))
        
        # Add Widgets
        self.layout.addWidget(self.moveForward, 0,0)
        self.layout.addWidget(self.moveBackward, 0,1)
        self.layout.addWidget(self.moveRight, 1,0)
        self.layout.addWidget(self.moveLeft, 1,1)
        self.layout.addWidget(self.Stop, 2,0,1,0)
        self.layout.addWidget(self.label1, 3,0,1,0)
        self.layout.addWidget(self.label2, 4,0)
        self.layout.addWidget(self.textBox, 4,1)

    def commInit(self):
        self.ser.baudrate = 9600
        self.ser.port = 'COM5'
        if not self.ser.is_open:
            self.ser.open()
        if self.ser.is_open:
            print("Connect to "+self.ser.port)
            self.label1.setText("Status: Connect to "+ self.ser.port)
            self.label1.adjustSize()
        else:
            print("Disconnect")
            self.label1.setText("Status: Disconnect")
            self.label1.adjustSize()

    def send_command(self):
        direction = bytes(self.direction, 'utf-8')
        speed = int(self.textBox.text())
        if speed >= 100:
            self.speed = "0"
        else:
            self.speed = str(int(speed/10))
        speed = bytes(self.speed, 'utf-8')
        self.ser.write(direction)
        self.ser.write(speed)
        print("Direction: ", direction)
        print("Speed: ", speed)

    def on_click_fwd(self):
        self.direction = "F"
        self.send_command()

    def on_click_bwd(self):
        self.direction = "B"
        self.send_command()

    def on_click_right(self):
        self.direction = "R"
        self.send_command()

    def on_click_left(self):
        self.direction = "L"
        self.send_command()

    def on_click_stop(self):
        self.direction = "S"
        self.send_command()
    
if __name__ == "__main__":
    qapp = QtWidgets.QApplication(sys.argv)
    app = ApplicationWindow()
    app.show()
    qapp.exec_()