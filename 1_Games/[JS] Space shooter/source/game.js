var canvas 	= document.getElementById('game'); 
var context = canvas.getContext('2d');

var ship;
var shipShield;
var tick;
var meteors = [];
var fires = [];
var booms = [];
var ultimateMod = false;

var meteorImg = new Image();
meteorImg.src = 'img\\meteor.png';
var shieldImg = new Image();
shieldImg.src = 'img\\shield.png';
var fireImg = new Image();
fireImg.src = 'img\\fire.png';
var shipImg = new Image();
shipImg.src = 'img\\ship.png';
var boomImg = new Image();
boomImg.src = 'img\\boom.png';
var backgroundImg = new Image();
backgroundImg.src = 'img\\background.png';

var overlordAlpha = 0.9, overlordAlphaGrow = false;
var overlordImage 	= new Image();//document.getElementById('overlordImage'); 
overlordImage.src = 'img\\overlord.jpg';


backgroundImg.onload = function () {
	init();
	loop();
}

function init(){
	//canvas.width = backgroundImg.width;

	canvas.addEventListener("mousemove",  function(event) {	
		ship.x=event.offsetX - shipImg.width / 2;
		ship.y=event.offsetY - shipImg.height / 2;
	});

	window.addEventListener("keydown",  function(event) {	
		if(event.key.toLowerCase() == "u")
			ultimateMod = !ultimateMod;
	});

	ship = {
		x: 	 	300,
		y: 		300
	};

	shipShield ={
		animx: 0,
		animy: 0,
		shieldCapacity: 10,
		ticksForRegen: 42,
		isAnim: false
	};

	tick = 0;
}

function loop(){
	update();
	render();
	requestAnimFrame(loop);
}

function update(){
	++tick;

	if(!ultimateMod && canvas.height - backgroundImg.height + tick / 3 >= 0)
		ultimateMod = true;
	
		if (tick % (ultimateMod ? 3 : 7) == 0) {
		meteors.push({
			angle: 0,
			dxangle: Math.random() * 0.2 - 0.1,
			x: Math.random() * 550,
			y: -50,
			dx: Math.random() * 2 - 1 + (ultimateMod && tick % 50 == 0? (26 * (tick / 50 % 2 ? -1 : 1)) : 0),
			dy: Math.random() * (ultimateMod ? 12 : 10) + (ultimateMod ? 1.5 : 1),
			isNeedToDelete: false
		});
	}

	if(tick % (ultimateMod ? 14 : 21) == 0){
		if(ultimateMod)
			fires.push({
				x:ship.x + shipImg.width / 2 - shipImg.width / 6,
				y:ship.y - shipImg.height, 
				dx: -1, 
				dy: -5,
				isNeedToDelete: false
			});
		fires.push({
			x:ship.x + shipImg.width / 2 - shipImg.width / 6,
			y:ship.y - shipImg.height, 
			dx: 0, 
			dy: -5.2,
			isNeedToDelete: false
		});
		if(ultimateMod)
			fires.push({
				x:ship.x + shipImg.width / 2 - shipImg.width / 6,
				y:ship.y - shipImg.height, 
				dx: 1, 
				dy: -5,
				isNeedToDelete: false
			});
	}

	for (i in meteors) {
		meteors[i].x += meteors[i].dx;
		meteors[i].y += meteors[i].dy;
		meteors[i].angle += meteors[i].dxangle;
		
		if (meteors[i].x <= -meteorImg.width / 2 || 
				meteors[i].x >= canvas.width - meteorImg.width / 2) 
			meteors[i].dx = -meteors[i].dx;
		if (meteors[i].y >= canvas.height + meteorImg.height) 
			meteors[i].isNeedToDelete = true;
		
		for (j in fires) {
			if( fires[j].isNeedToDelete == false &&
				Math.abs(meteors[i].x  + meteorImg.width / 2  - fires[j].x - shipImg.width / 6) < meteorImg.width / 2 && 
				Math.abs(meteors[i].y + meteorImg.height / 2 - fires[j].y - shipImg.height / 2) < meteorImg.height / 2){
				meteors[i].isNeedToDelete = true;
				fires[j].isNeedToDelete = true;
				booms.push({
					x:meteors[i].x - meteorImg.width / 2, y:meteors[i].y - meteorImg.height / 2,
					animx:0, animy:0
				});
			}
		}

		if( meteors[i].isNeedToDelete == false &&
			Math.abs(meteors[i].x  + meteorImg.width / 2  - ship.x - shipImg.width / 2) < meteorImg.width / 2 && 
			Math.abs(meteors[i].y + meteorImg.height / 2 - ship.y - shipImg.height / 2) < meteorImg.height / 2
		){
			if(!shipShield.isAnim){
				shipShield.isAnim = true;
				--shipShield.shieldCapacity;
			}
			meteors[i].isNeedToDelete = true;
			booms.push({
				x:meteors[i].x - meteorImg.width / 2, y:meteors[i].y - meteorImg.height / 2,
				animx:0, animy:0
			});
		}
	}

	for (i in fires) {
		fires[i].x = fires[i].x + fires[i].dx;
		fires[i].y = fires[i].y + fires[i].dy;
		
		if (fires[i].y < -shipImg.height)
			fires[i].isNeedToDelete = true;
	}

	for (i in meteors) 
	if (meteors[i].isNeedToDelete) 
		meteors.splice(i, 1);

	for (i in fires) 
		if(fires[i].isNeedToDelete)
			fires.splice(i, 1);

	for (i in booms) {
		booms[i].animx += 0.5;
		if (booms[i].animx == 8) {
			booms[i].animy++;
			booms[i].animx = 0
		}
		if (booms[i].animy == 8) 
			booms.splice(i, 1);
	}

	if(shipShield.isAnim){
		shipShield.animx += 1;
		if (shipShield.animx == 5) {
			shipShield.animy++; 
			shipShield.animx = 0
		}
		if (shipShield.animy == 4) {
			shipShield.animx = 0;
			shipShield.animy = 0;
			shipShield.isAnim = false;
		}
	}
}

function render(){
	context.clearRect(0, 0, canvas.width, canvas.height);
	var newYBackground = canvas.height - backgroundImg.height + tick / 3;
	context.drawImage(backgroundImg, 
		0, ((newYBackground < 0) ? newYBackground : 0),
		backgroundImg.width, backgroundImg.height);

	for (i in fires) 
		context.drawImage(fireImg, fires[i].x, fires[i].y, shipImg.width / 3, shipImg.height);

	context.drawImage(shipImg, ship.x, ship.y, shipImg.width, shipImg.height);
	context.drawImage(shieldImg, 
		shieldImg.width / 5 * Math.floor(shipShield.animx), shieldImg.height / 4 * Math.floor(shipShield.animy),
		shieldImg.width / 5, shieldImg.height / 4, 
		ship.x - shipImg.width / 1.5, ship.y - shipImg.height / 1.5, 
		shipImg.width * 2.3, shipImg.height * 2.5);

	for (i in meteors) {
		//context.drawImage(meteorImg, meteors[i].x, meteors[i].y, meteorImg.width, meteorImg.height);
		context.save();
		context.translate(meteors[i].x + meteorImg.width / 2, meteors[i].y + meteorImg.height / 2);
		context.rotate(meteors[i].angle);
		context.drawImage(meteorImg, -meteorImg.width / 2, -meteorImg.height / 2, meteorImg.width, meteorImg.height);
		context.restore();
	}

	for (i in booms)
		context.drawImage(boomImg,
			boomImg.width / 8 * Math.floor(booms[i].animx), boomImg.height / 8 * Math.floor(booms[i].animy),
			boomImg.width / 8, boomImg.height / 8,
			booms[i].x, booms[i].y, 
			boomImg.width / 8, boomImg.height / 8);

	if(ultimateMod){
		context.globalAlpha = overlordAlpha;

		if(overlordAlphaGrow)
			overlordAlpha += 0.03;
		else
			overlordAlpha -= 0.05;

		if(overlordAlpha >= 1.3)
			overlordAlphaGrow = false;
		else if(overlordAlpha <= 0.1)
			overlordAlphaGrow = true;
		
		context.drawImage(overlordImage,
			0, 0,
			600, 600
		)
		context.globalAlpha = 1;
	}
}

var requestAnimFrame = (function(){
    return window.requestAnimationFrame    ||
        window.webkitRequestAnimationFrame ||
        window.mozRequestAnimationFrame    ||
        window.oRequestAnimationFrame      ||
        window.msRequestAnimationFrame     ||
        function(callback){
            window.setTimeout(callback, 1000 / 20);
        };
})();