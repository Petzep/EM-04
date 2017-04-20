import QtQuick 2.7

Item {
    property bool on: true 

	 function paintOutlinePath(ctx) {
		ctx.beginPath();
		ctx.moveTo(width * 0.30, height * 0.38);
		ctx.arcTo(width*0.5, height * 0.51, width * 0.30, height * 0.64, width*0.13);
		ctx.lineTo(width * 0.30, height * 0.64)
		ctx.moveTo(width * 0.30, height * 0.38);
		ctx.arcTo(width*0.27, height * 0.51, width * 0.30, height * 0.64, width*0.44);
		ctx.lineTo(width * 0.30, height * 0.64)
		ctx.moveTo(width * 0.70, height * 0.38);
		ctx.arcTo(width*0.5, height * 0.51, width * 0.70, height * 0.64, width*0.13);
		ctx.lineTo(width * 0.70, height * 0.64)
		ctx.moveTo(width * 0.70, height * 0.38);
		ctx.arcTo(width*0.73, height * 0.51, width * 0.70, height * 0.64, width*0.44);
		ctx.lineTo(width * 0.70, height * 0.64)

		ctx.moveTo(width * 0.20, height * 0.34);
		ctx.lineTo(width * 0.09, height * 0.30);
		ctx.moveTo(width * 0.18, height * 0.50);
		ctx.lineTo(width * 0.05, height * 0.50);
		ctx.moveTo(width * 0.20, height * 0.64);
		ctx.lineTo(width * 0.09, height * 0.70);

		ctx.moveTo(width * 0.80, height * 0.34);
		ctx.lineTo(width * 0.91, height * 0.30);
		ctx.moveTo(width * 0.82, height * 0.50);
		ctx.lineTo(width * 0.95, height * 0.50);
		ctx.moveTo(width * 0.80, height * 0.64);
		ctx.lineTo(width * 0.91, height * 0.70);
    }

    Canvas {
        id: backgroundCanvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
			ctx.lineWidth = on?3:1;
			ctx.strokeStyle = on?"green":"black";

            paintOutlinePath(ctx);
			ctx.stroke();
        }
    }
}