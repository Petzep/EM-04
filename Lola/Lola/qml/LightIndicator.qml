import QtQuick 2.2

Item {
    property bool dim: true
    property bool on: true

	//lampjes
    function paintOutlinePathFill(ctx) {
       ctx.beginPath();
		ctx.moveTo(width * 0.5, height * 0.23);
		ctx.arcTo(width*0.61, height * 0.20, width * 0.78, height * 0.24, width*0.4);
		ctx.lineTo(width * 0.8, height * 0.25);
		ctx.arcTo(width*1.3, height * 0.5, width * 0.8, height * 0.75, width*0.25);
		ctx.lineTo(width * 0.8, height * 0.75);
		ctx.lineTo(width * 0.5, height * 0.77);
		ctx.moveTo(width * 0.78, height * 0.76);
		ctx.arcTo(width*0.61, height * 0.80, width * 0.5, height * 0.77, width*0.4);
		ctx.lineTo(width * 0.8, height * 0.75);
		ctx.moveTo(width * 0.5, height * 0.23);
		ctx.arcTo(width * 0.40, height * 0.5, width * 0.5, height * 0.76, width*0.64);
		ctx.lineTo(width * 0.5, height * 0.77);
    }


	 function paintOutlinePath(ctx) {
		ctx.beginPath();
		ctx.moveTo(width * 0.5, height * 0.23);
		ctx.arcTo(width*0.61, height * 0.20, width * 0.78, height * 0.24, width*0.4);
		ctx.lineTo(width * 0.8, height * 0.25);
		ctx.arcTo(width*1.3, height * 0.5, width * 0.8, height * 0.75, width*0.25);
		ctx.lineTo(width * 0.8, height * 0.75);
		ctx.moveTo(width * 0.5, height * 0.77);
		ctx.arcTo(width*0.61, height * 0.80, width * 0.78, height * 0.76, width*0.4);
		ctx.lineTo(width * 0.8, height * 0.75);
		ctx.moveTo(width * 0.5, height * 0.23);
		ctx.arcTo(width * 0.40, height * 0.5, width * 0.5, height * 0.76, width*0.64);
		ctx.lineTo(width * 0.5, height * 0.77);
    }

	//Streepjes
	 function paintLightlinePath(ctx) {
		ctx.beginPath();

		ctx.moveTo(width * 0.1, height * 0.23);
		ctx.lineTo(width * 0.4, height * 0.23);
		ctx.moveTo(width * 0.1, height * 0.36);
		ctx.lineTo(width * 0.38, height * 0.36);
		ctx.moveTo(width * 0.1, height * 0.50);
		ctx.lineTo(width * 0.35, height * 0.50);
		ctx.moveTo(width * 0.1, height * 0.64);
		ctx.lineTo(width * 0.38, height * 0.64);
		ctx.moveTo(width * 0.1, height * 0.78);
		ctx.lineTo(width * 0.4, height * 0.78);
    }

		 function paintDimLightlinePath(ctx) {
		ctx.beginPath();

		ctx.moveTo(width * 0.1, height * 0.33);
		ctx.lineTo(width * 0.4, height * 0.23);
		ctx.moveTo(width * 0.1, height * 0.46);
		ctx.lineTo(width * 0.38, height * 0.36);
		ctx.moveTo(width * 0.1, height * 0.60);
		ctx.lineTo(width * 0.35, height * 0.50);
		ctx.moveTo(width * 0.1, height * 0.74);
		ctx.lineTo(width * 0.38, height * 0.64);
		ctx.moveTo(width * 0.1, height * 0.88);
		ctx.lineTo(width * 0.4, height * 0.78);
    }

    Canvas {
        id: backgroundCanvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
			ctx.lineWidth = on?3:1;
			ctx.strokeStyle = on?(dim?"green":"blue"):"black";

            paintOutlinePath(ctx);
			ctx.stroke();
			dim?paintDimLightlinePath(ctx):paintLightlinePath(ctx);
            ctx.stroke();
        }
    }
}
