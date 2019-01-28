

$(function(){
	placeBoard()
	placeChess()
	setDraggable()
})

function placeBoard(){
	$('.chessboard').html('')
	for (var i = 0; i < 8; i++) {
		for (var j = 0; j < 8; j++){
		if(i % 2 == j % 2)
			$('.chessboard').append('<div id="sqr' + i + j + '" class="square whiteSquare">')
		else
			$('.chessboard').append('<div id="sqr' + i + j + '" class="square blackSquare">')
		}
	}
}

function placeChess(){
	for (var i = 0; i < 8; i++){
		$('#sqr1' + i).html('<div id="fig_wp' + i + '" class="figure whiteFigure">&#9817</div>')
		$('#sqr6' + i).html('<div id="fig_bp' + i + '" class="figure blackFigure">&#9823</div>')
	}

	$('#sqr00').html('<div id="fig_wt1" class="figure whiteFigure">&#9814</div>')
	$('#sqr01').html('<div id="fig_wh1" class="figure whiteFigure">&#9816</div>')
	$('#sqr02').html('<div id="fig_wo1" class="figure whiteFigure">&#9815</div>')
	$('#sqr03').html('<div id="fig_wq" class="figure whiteFigure">&#9813</div>')
	$('#sqr04').html('<div id="fig_wk" class="figure whiteFigure">&#9812</div>')
	$('#sqr05').html('<div id="fig_wo2" class="figure whiteFigure">&#9815</div>')
	$('#sqr06').html('<div id="fig_wh2" class="figure whiteFigure">&#9816</div>')
	$('#sqr07').html('<div id="fig_wt2" class="figure whiteFigure">&#9814</div>')

	$('#sqr70').html('<div id="fig_bt1" class="figure blackFigure">&#9820</div>')
	$('#sqr71').html('<div id="fig_bh1" class="figure blackFigure">&#9822</div>')
	$('#sqr72').html('<div id="fig_bo1" class="figure blackFigure">&#9821</div>')
	$('#sqr73').html('<div id="fig_bq" class="figure blackFigure">&#9819</div>')
	$('#sqr74').html('<div id="fig_bk" class="figure blackFigure">&#9818</div>')
	$('#sqr75').html('<div id="fig_bo2" class="figure blackFigure">&#9821</div>')
	$('#sqr76').html('<div id="fig_bh2" class="figure blackFigure">&#9822</div>')
	$('#sqr77').html('<div id="fig_bt2" class="figure blackFigure">&#9820</div>')
}

function setDraggable(){
	$('.whiteFigure').draggable()
	$('.blackFigure').draggable()
}