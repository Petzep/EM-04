import QtQuick 2.7

Item {
    property bool on: true 

	 function paintOutlinePath(ctx) {
		ctx.beginPath();
		ctx.moveTo(width * 0.11, height * 0.30);
		ctx.lineTo(width * 0.23, height * 0.30);
		ctx.lineTo(width * 0.23, height * 0.23);
		ctx.lineTo(width * 0.31, height * 0.23);
		ctx.lineTo(width * 0.31, height * 0.30);
		ctx.lineTo(width * 0.68, height * 0.30);
		ctx.lineTo(width * 0.68, height * 0.23);
		ctx.lineTo(width * 0.76, height * 0.23);
		ctx.lineTo(width * 0.76, height * 0.30);
		ctx.lineTo(width * 0.88, height * 0.30);
		ctx.lineTo(width * 0.88, height * 0.74);
		ctx.lineTo(width * 0.11, height * 0.74);
		ctx.lineTo(width * 0.11, height * 0.30);
		ctx.moveTo(width * 0.22, height * 0.52);
		ctx.lineTo(width * 0.35, height * 0.52);
		ctx.moveTo(width * 0.64, height * 0.52);
		ctx.lineTo(width * 0.78, height * 0.52);
		ctx.moveTo(width * 0.71, height * 0.45);
		ctx.lineTo(width * 0.71, height * 0.59);
    }

    Canvas {
        id: backgroundCanvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
			ctx.lineWidth = 1;
			ctx.strokeStyle = "black";

            paintOutlinePath(ctx);
			ctx.stroke();
        }
	}
	
	Canvas {
        id: foregroundCanvas
        anchors.fill: parent
        visible: on

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
			ctx.lineWidth = 3;
			ctx.strokeStyle = "red";

            paintOutlinePath(ctx);
			ctx.stroke();
        }
    }
}
