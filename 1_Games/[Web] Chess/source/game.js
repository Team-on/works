var map = new Array(8, 8)

$(function(){
	placeBoard()
	placeChess()
	setDraggable()
	setDroppable()
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
		map[1][i] = 0;
		$('#sqr1' + i).html('<div id="fig_wp' + i + '" class="figure whiteFigure">&#9817</div>');
		map[0][i] = 1;
		z$('#sqr6' + i).html('<div id="fig_bp' + i + '" class="figure blackFigure">&#9823</div>');
	}

	map[0][0] = $('#sqr00').html('<div id="fig_wt1" class="figure whiteFigure">&#9814</div>')
	map[0][1] = $('#sqr01').html('<div id="fig_wh1" class="figure whiteFigure">&#9816</div>')
	map[0][2] = $('#sqr02').html('<div id="fig_wo1" class="figure whiteFigure">&#9815</div>')
	map[0][3] = $('#sqr03').html('<div id="fig_wq" class="figure whiteFigure">&#9813</div>')
	map[0][4] = $('#sqr04').html('<div id="fig_wk" class="figure whiteFigure">&#9812</div>')
	map[0][5] = $('#sqr05').html('<div id="fig_wo2" class="figure whiteFigure">&#9815</div>')
	map[0][6] = $('#sqr06').html('<div id="fig_wh2" class="figure whiteFigure">&#9816</div>')
	map[0][7] = $('#sqr07').html('<div id="fig_wt2" class="figure whiteFigure">&#9814</div>')

	map[7][0] = $('#sqr70').html('<div id="fig_bt1" class="figure blackFigure">&#9820</div>')
	map[7][1] = $('#sqr71').html('<div id="fig_bh1" class="figure blackFigure">&#9822</div>')
	map[7][2] = $('#sqr72').html('<div id="fig_bo1" class="figure blackFigure">&#9821</div>')
	map[7][3] = $('#sqr73').html('<div id="fig_bq" class="figure blackFigure">&#9819</div>')
	map[7][4] = $('#sqr74').html('<div id="fig_bk" class="figure blackFigure">&#9818</div>')
	map[7][5] = $('#sqr75').html('<div id="fig_bo2" class="figure blackFigure">&#9821</div>')
	map[7][6] = $('#sqr76').html('<div id="fig_bh2" class="figure blackFigure">&#9822</div>')
	map[7][7] = $('#sqr77').html('<div id="fig_bt2" class="figure blackFigure">&#9820</div>')
}

function setDraggable(){
	$('.whiteFigure').draggable()
	$('.blackFigure').draggable()
}

function setDroppable(){
	$('.square').droppable({
		drop: function (event, ui){
			console.log(this.id)
			console.log(ui.draggable.attr('id'))
			ui.draggable.removeAttr('style')
			$('#' + ui.draggable.attr('id')).appendTo('#' + this.id)
		}
	})
}