import QtQuick 2.7

Item {
    id: valueSource
	objectName: "valueSource"
    property real kph: 0
    property real rpm: 1
    property real fuel: 0.85
    property string gear: "N"
    
    property bool leftArrow: false
	property bool rightArrow: false
	property bool smallOn: false
	property bool dimOn: false
	property bool fullOn: false
    property real temperature: 23
    property bool start: false
	property bool batOn: false
}
