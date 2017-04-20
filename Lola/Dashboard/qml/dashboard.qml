import QtQuick 2.7
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Window {
    id: root
	objectName: "dashboardWindow"
	width: 800
    height: 480
    visibility: "Windowed"
    color: "#161616"
    title: "Lola Dashboard"

   	signal exit()

    ValueSource {
        id: valueSource
    }

    // Dashboards are typically in a landscape orientation, so we need to ensure
    // our height is never greater than our width.
    Item {
        id: container
        width: root.width
        height: Math.min(root.width, root.height)
        anchors.centerIn: parent
		focus: true
		Keys.onPressed: {
        if (event.key == Qt.Key_0) {
            root.exit()
            event.accepted = true;
			console.log("Exiting")
			}
		}
		
		Column {
				id: dashColumn
				anchors.horizontalCenter: parent.horizontalCenter
				anchors.verticalCenter: parent.verticalCenter
				spacing: container.height * 0.02

			Row {
				id: lightRow
				spacing: container.width * 0.02
				anchors.horizontalCenter: parent.horizontalCenter
				anchors.verticalCenter: parent.verticalCenter + 0.5 * parent.height
					LightIndicator {
						id: dimIndicator
						anchors.verticalCenter: parent.verticalCenter
						width: height
						height: container.height * 0.1 - gaugeRow.spacing

						dim: true
						on: valueSource.dimOn
					}

					LightSmallIndicator {
						id: smallIndicator
						anchors.verticalCenter: parent.verticalCenter
						width: height
						height: container.height * 0.1 - gaugeRow.spacing

						on: valueSource.smallOn;
					}

					Text {
						id: dnrText
						text: valueSource.gear
						color: "white"
						font.family: "Helvetica"
						font.pointSize: 24
						antialiasing: true
					}

					LightIndicator {
						id: fullIndicator
						anchors.verticalCenter: parent.verticalCenter
						width: height
						height: container.height * 0.1 - gaugeRow.spacing

						dim: false
						on: valueSource.fullOn
					}

					StatIndicator {
						id: batIndicator
						anchors.verticalCenter: parent.verticalCenter
						width: height
						height: container.height * 0.1 - gaugeRow.spacing

						on: valueSource.batOn
					}
				}
			Row {
				id: gaugeRow
				spacing: container.width * 0.02
				anchors.horizontalCenter: parent.horizontalCenter
				anchors.verticalCenter: parent.verticalCenter - 0.5 * parent.height

				TurnIndicator {
					id: leftIndicator
					anchors.verticalCenter: parent.verticalCenter
					width: height
					height: container.height * 0.1 - gaugeRow.spacing

					direction: Qt.LeftArrow
					on: valueSource.leftArrow;
				}

				Item {
					width: height
					height: container.height * 0.25 - gaugeRow.spacing
					anchors.verticalCenter: parent.verticalCenter

					CircularGauge {
						id: fuelGauge
						value: valueSource.fuel
						maximumValue: 1
						y: parent.height / 2 - height / 2 - container.height * 0.01
						width: parent.width
						height: parent.height * 0.7

						style: IconGaugeStyle {
							id: fuelGaugeStyle

							icon: "qrc:/images/elec-icon.png"
							minWarningColor: Qt.rgba(0.5, 0, 0, 1)

							tickmarkLabel: Text {
								color: "white"
								visible: styleData.value === 0 || styleData.value === 1
								font.pixelSize: fuelGaugeStyle.toPixels(0.225)
								text: styleData.value === 0 ? "E" : (styleData.value === 1 ? "F" : "")
							}
						}
					}

					CircularGauge {
						value: valueSource.temperature
						maximumValue: 80
						width: parent.width
						height: parent.height * 0.7
						y: parent.height / 2 + container.height * 0.01

						style: IconGaugeStyle {
							id: tempGaugeStyle

							icon: "qrc:/images/temperature-icon.png"
							tickmarkStepSize: 80;
							maxWarningColor: Qt.rgba(0.5, 0, 0, 1)

							tickmarkLabel: Text {
								color: "white"
								font.pixelSize: tempGaugeStyle.toPixels(0.225)
								text: styleData.value === 0 ? "C" : (styleData.value === 80 ? "H" : "")
							}
						}
					}
				}

				CircularGauge {
					id: speedometer
					value: Math.abs(valueSource.kph)
					anchors.verticalCenter: parent.verticalCenter
					maximumValue: 120
					// We set the width to the height, because the height will always be
					// the more limited factor. Also, all circular controls letterbox
					// their contents to ensure that they remain circular. However, we
					// don't want to extra space on the left and right of our gauges,
					// because they're laid out horizontally, and that would create
					// large horizontal gaps between gauges on wide screens.
					width: height
					height: container.height * 0.5

					style: DashboardGaugeStyle {}
				}

				CircularGauge {
					id: tachometer
					width: height
					height: container.height * 0.25 - gaugeRow.spacing
					value: valueSource.rpm
					maximumValue: 160
					anchors.verticalCenter: parent.verticalCenter

					style: TachometerStyle {}
				}

				TurnIndicator {
					id: rightIndicator
					anchors.verticalCenter: parent.verticalCenter
					width: height
					height: container.height * 0.1 - gaugeRow.spacing

					direction: Qt.RightArrow
					on: valueSource.rightArrow
				}
			}

        }
    }
}
