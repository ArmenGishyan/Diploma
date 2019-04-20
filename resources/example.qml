import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    visible: true
    width : 640
    height : 480
    Repeater {
        model: rectlist
        delegate: Rectangle {
            x : modelData.x
            y : modelData.y
            width: modelData.width
            height: modelData.height
            color : "red"
        }
    }

}
