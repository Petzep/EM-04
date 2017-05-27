import QtQuick 2.7

Item {
    id: valueSource
	objectName: "valueSource"
    property real kph: 0
    property real rpm: 0
    property real fuel: 0
    property string gear: "-"
    
    property bool leftArrow: false
	property bool rightArrow: false
	property bool smallOn: false
	property bool dimOn: false
	property bool fullOn: false
    property real temperature: 0
	property bool batOn: false

	SequentialAnimation {
		running: true
        loops: 1
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 0
                    to: 120
                    duration: 1000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutQuad
                    from: 0
                    to: 160
                    duration: 1000
                }
				NumberAnimation {
                    target: valueSource
                    property: "fuel"
                    easing.type: Easing.InOutQuad
                    from: 45
                    to: 58.8
                    duration: 1000
                }
				NumberAnimation {
                    target: valueSource
                    property: "temperature"
                    easing.type: Easing.InOutQuad
                    from: 0
                    to: 80
                    duration: 1000
                }
            }
            ParallelAnimation {
                    NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 120
                    to: 0
                    duration: 1000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutQuad
                    from: 160
                    to: 0
                    duration: 1000
                }
				NumberAnimation {
                    target: valueSource
                    property: "fuel"
                    easing.type: Easing.InOutQuad
                    from: 58.8
                    to: 45
                    duration: 1000
                }
				NumberAnimation {
                    target: valueSource
                    property: "temperature"
                    easing.type: Easing.InOutQuad
                    from: 80
                    to: 0
                    duration: 1000
                }
            }
		}
}
