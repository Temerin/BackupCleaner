import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

import FilesTableModel

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("File View")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

//        RowLayout {

//            Label {
//                text: qsTr("Interface:")
//            }
//            ComboBox {
//                Layout.fillWidth: true
//                implicitHeight: 40
//            }
//        }

        Label {
            text: qsTr("Files:")
        }

        ResizableColumnsTableView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            model: FilesTableModel {}
            columnWidths: [250, 200, 100]
        }

//        RowLayout {
//            Layout.alignment: Qt.AlignRight

//            Button {
//                text: "Add"
//            }

//            Button {
//                text: "Edit"
//            }

//            Button {
//                text: "Delete"
//            }
//        }
    }
}
