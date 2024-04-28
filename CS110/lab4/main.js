let dbnc = Date.now();

function clear_articles() {
	let article_container = document.getElementsByClassName("article-container")[0];
	
	article_container.innerHTML = "";
}

function add_article(title = "?) Dummy Article", date = "YYYY-MM-DD", img_src, desc) {
	img_src = img_src || "https://cdn4.iconfinder.com/data/icons/thin-gui-elements-2/24/thin-1550_website_error_missing_404-512.png";
	desc = desc || "404 Missing";

	let individual_article = `\
		<div class="article">
			<div class="a-meta">
				<div class="am-title">${title}</div>
				<div class="am-date">${date}</div>
			</div>
			<div class="a-details">
				<img class="ad-thumbnail" src="${img_src}">
				<div class="ad-blurb">${desc}</div>
			</div>
		</div>
	`

	let article_container = document.getElementsByClassName("article-container")[0];
	article_container.innerHTML += individual_article;
}

var getting = false; //debounce
async function update_articles() {
	if (getting) return;
	getting = true;

	clear_articles();

	let dif = (Date.now() - dbnc) / 1000;
	console.log("So this is the dif " + dif);
	if (dif < 15) await new Promise(r => setTimeout(r, (15 - dif)*1000));
	dbnc = Date.now();

	//get settings
	let srtbies = document.getElementsByName("sortbyer");
	let srtby = "Emailed";
	if (srtbies[0].checked) srtby = "Viewed";
	if (srtbies[1].checked) srtby = "Shared";

	let tframes = document.getElementsByName("timeframe");
	let tfrme = "Month";
	if (tframes[0].checked) tfrme = "Day"
	if (tframes[1].checked) tfrme = "Week"

	const url = "";
	fetch(url).then(res => res.json).then(data => {
		console.log(data)
		getting = false;
	}).catch(err => {
		console.log(err)
		getting = false;
	})//*/
}