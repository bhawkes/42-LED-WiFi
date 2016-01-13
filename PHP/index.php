<?php

	if (!empty($_GET)){

		$file = 'state.txt';
		$state = file_get_contents($file);

		if($_GET['toggle']){

			$led = $_GET['toggle'];

			$state[$led] = ($state[$led] === '1' ? '0' : '1');

			file_put_contents($file, $state);

			echo $state;

		} else if($_GET['unlight']){

			$led = $_GET['unlight'];

			if($led === 'all'){
				$state = '{000000000000000000000000000000000000000000}';
			} else {
				$state[$led] = '0';
			}

			file_put_contents($file, $state);
			echo $state;

		} else if($_GET['light']){

				$led = $_GET['light'];

				if($led === 'all'){
					$state = '{111111111111111111111111111111111111111111}';
				} else {
					$state[$led] = '1';
				}

				file_put_contents($file, $state);
				echo $state;

		} else if($_GET['read']){

			echo $state;

		} else{
			echo 'query error';
		}
	} else {
	?>


	<!DOCTYPE html>
	<html>
		<head>
			<meta charset="utf-8">
			<title>LED CONTROL</title>
			<meta name="viewport" content="width=device-width, user-scalable=no, minimum-scale=1.0, maximum-scale=1.0"/>
		</head>
		<style media="screen">
			body{margin:0;font-family: sans-serif;background-color: #4D4D4D;}
			*{user-select:none;-webkit-user-select:none;}
			h1{
				text-align: center;color: #FCEE21;
			}
			h2{
				text-decoration: underline;
				cursor: pointer;
				margin: 20px;
			}
			#light-all{
				float:left;
				color: #FCEE21;
			}
			#unlight-all{
				float: right;
				color: #5E5D49;
			}
			.leds{font-size: 0;max-width: 600px;margin:0 auto;}
			.led{width:14.285%;padding-top:14.285%;background-color: #5E5D49;display: inline-block;cursor: pointer;clip-path: circle(40% at 50% 50%);-webkit-clip-path: circle(40% at 50% 50%);-webkit-tap-highlight-color: rgba(0, 0, 0, 0);}
			.lit{background-color: #FCEE21;}
		</style>
		<body>

			<h1>LED control</h1>

			<div class="leds">
				<div class="led">1</div>
				<div class="led">2</div>
				<div class="led">3</div>
				<div class="led">4</div>
				<div class="led">5</div>
				<div class="led">6</div>
				<div class="led">7</div>
				<div class="led">8</div>
				<div class="led">9</div>
				<div class="led">10</div>
				<div class="led">11</div>
				<div class="led">12</div>
				<div class="led">13</div>
				<div class="led">14</div>
				<div class="led">15</div>
				<div class="led">16</div>
				<div class="led">17</div>
				<div class="led">18</div>
				<div class="led">19</div>
				<div class="led">20</div>
				<div class="led">21</div>
				<div class="led">22</div>
				<div class="led">23</div>
				<div class="led">24</div>
				<div class="led">25</div>
				<div class="led">26</div>
				<div class="led">27</div>
				<div class="led">28</div>
				<div class="led">29</div>
				<div class="led">30</div>
				<div class="led">31</div>
				<div class="led">32</div>
				<div class="led">33</div>
				<div class="led">34</div>
				<div class="led">35</div>
				<div class="led">36</div>
				<div class="led">37</div>
				<div class="led">38</div>
				<div class="led">39</div>
				<div class="led">40</div>
				<div class="led">41</div>
				<div class="led">42</div>
			</div>

			<h2 id="light-all">light all</h2>
			<h2 id="unlight-all">light none</h2>

			<script type="text/javascript">

			var ledState = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

			// standard toggle
			var clickOrTouch = (('ontouchend' in window)) ? 'touchend' : 'click';
			for (var i = 0; i < document.getElementsByClassName("led").length; i++) {
				document.getElementsByClassName("led")[i].addEventListener(clickOrTouch, function (e) {
					e.stopPropagation();
					e.preventDefault();
					ledState[this.innerHTML-1] = ledState[this.innerHTML-1] === '0' ? '1' : '0';
					update('?toggle='+this.innerHTML);
					document.getElementsByClassName("led")[this.innerHTML-1].className = "led " + (ledState[this.innerHTML-1] === '1' ? 'lit' : '');
				}, false);
			}

			// light up all leds
			document.getElementById('light-all').addEventListener('click',function (e) {
				e.preventDefault();
				update('?light=all');
				for (var i = 0; i < 42; i++) {
					ledState[i] = '0';
					document.getElementsByClassName("led")[i].className = "led lit";
				}
			});

			// unlight all leds
			document.getElementById('unlight-all').addEventListener('click',function (e) {
				e.preventDefault();
				update('?unlight=all');
				for (var i = 0; i < 42; i++) {
					ledState[i] = '1';
					document.getElementsByClassName("led")[i].className = "led";
				}
			});

			// stop scroll on touch devices
			document.addEventListener('touchmove',function (e) {
				e.preventDefault();
			})

			function update(url,refresh){
				var xhr = new XMLHttpRequest();
				xhr.open('GET', encodeURI(url));
				xhr.onload = function() {
						if (xhr.status === 200) {
								parseReply(xhr.responseText,refresh);
						}
						else {
						}
				};
				xhr.send();
			}

			function parseReply(reply,refresh) {
				console.log(reply);
				for (var i = 0; i < 42; i++) {
					ledState[i] = reply[i+1];
					if(refresh){
						document.getElementsByClassName("led")[i].className = "led "+(ledState[i] === '1' ? 'lit' : '');
					}
				}
			}

			update('?read=simple',true);
			</script>
		</body>
	</html>



	<?php } ?>
