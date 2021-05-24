# *********************************************
import sys
import random
import paho.mqtt.client as mqtt

from PySide6 import QtCore, QtWidgets, QtGui


# **********************************************
# MQTT Button Class
# **********************************************
class MQTTButton(QtWidgets.QWidget):
    def __init__(self):
        # - Initialize the parent class
        super().__init__()
        # - Class member to store the MQTT client object
        self.mqtt_client = None

        # - Text labels
        self.CurrentClient = QtWidgets.QLabel("0", alignment=QtCore.Qt.AlignCenter)
        # - Formatting the Font
        self.BigFont = QtGui.QFont('Arial', 150)
        self.CurrentClient.setFont(self.BigFont)
        # - Declaration of a layout container
        self.layout = QtWidgets.QVBoxLayout(self)
        self.layout.addWidget(self.CurrentClient)

    def set_client(self, new_mqtt_client):
        # - Assign the mqtt client
        self.mqtt_client = new_mqtt_client

    def on_message(self, client, userdata, message):
        # - Upon receiving a message, update the text
        self.CurrentClient.setText(str(message.payload.decode("utf-8")))


# - Main entry point
if __name__ == "__main__":
    # - Declaring the QT Application
    app = QtWidgets.QApplication([])
    # - Adding widgets
    widget = MQTTButton()
    # - MQTT Configuration
    mqtt_client = mqtt.Client()
    mqtt_client.connect("localhost")
    mqtt_client.on_message = widget.on_message
    mqtt_client.loop_start()
    mqtt_client.subscribe("test")
    widget.set_client(mqtt_client)
    widget.resize(800, 600)
    widget.show()
    sys.exit(app.exec())
