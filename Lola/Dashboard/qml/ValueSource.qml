import QtQuick 2.7

Item {
    id: valueSource
	objectName: "valueSource"
    property real kph: 0
    property real rpm: 1
    property real fuel: 0.85
    property string gear: {	
        var g;
        if (kph == 0) {
            return "N";
        }
        if (kph < 0) {
            return "R";
        }
        if (kph > 0) {
            return "D";
        }
    }
    property int turnSignal: gear == "N" && !start ? randomDirection() : -1
	property bool dimOn: true
	property bool fullOn: true
    property real temperature: 0.6
    property bool start: true
}
