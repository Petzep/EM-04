import QtQuick 2.2

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

    function randomDirection() {
        return Math.random() > 0.5 ? Qt.LeftArrow : Qt.RightArrow;
    }

    SequentialAnimation {
        running: true
        loops: 1

        // We want a small pause at the beginning, but we only want it to happen once.
        PauseAnimation {
            duration: 1000
        }

        PropertyAction {
            target: valueSource
            property: "start"
            value: false
        }

        SequentialAnimation {
            loops: Animation.Infinite

            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 0
                    to: 40
                    duration: 2500
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutQuad
                    from: 0.8
                    to: 120
                    duration: 1000
                }
            }
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 40
                    to: 60
                    duration: 4000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.InOutQuad
                    from: 120
                    to: 80
                    duration: 4000
                }
            }
			  ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    from: 60
                    to: 85
                    duration: 5000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.outSine
                    from: 80
                    to: 123
                    duration: 4000
                }
            }
            ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 0
                    duration: 5000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.OutQuad
                    to: 0
                    duration: 1000
                }
            }
			ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: -13
                    duration: 1000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.outBack
                    to: 60
                    duration: 1000
                }
            }
				ParallelAnimation {
                NumberAnimation {
                    target: valueSource
                    property: "kph"
                    easing.type: Easing.InOutSine
                    to: 0
                    duration: 1000
                }
                NumberAnimation {
                    target: valueSource
                    property: "rpm"
                    easing.type: Easing.OutQuad
                    to: 0
                    duration: 1000
                }
            }
            PauseAnimation {
                duration: 5000
            }
        }
    }
}
