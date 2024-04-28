const debounce_time = 15 //seconds

let dbnc = Date.now() - (debounce_time * 1000);

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
	add_article("Please wait, loading!");

	let dif = (Date.now() - dbnc) / 1000;
	console.log("So this is the dif " + dif);
	if (dif < 15) await new Promise(r => setTimeout(r, (15 - dif)*1000));
	dbnc = Date.now();

	//get settings
	let srtbies = document.getElementsByName("sortbyer");
	let srtby = "emailed";
	if (srtbies[0].checked) srtby = "viewed";
	if (srtbies[1].checked) srtby = "shared";

	let tframes = document.getElementsByName("timeframe");
	let tfrme = 30; //month
	if (tframes[0].checked) tfrme = 1 //day
	if (tframes[1].checked) tfrme = 7 //week

	//KhwR0H4oNA4NdXgMshnf3w6jRfST7Y7J
	const url = `https://api.nytimes.com/svc/mostpopular/v2/${srtby}/${tfrme}.json?api-key=KhwR0H4oNA4NdXgMshnf3w6jRfST7Y7J`;
	fetch(url).then(res => res.json()).then(data => {
		clear_articles();

		console.log(data)
		for (let i = 0; i < data.num_results; i++) {
			let article = data.results[i];

			if (article.media.length < 1) continue; //no media, skip

			let img_url = undefined;
			for (let j = 0; j < article.media.length; j++) {
				try{
					if (article.media[j].type == "image") {
						img_url = article.media[j]["media-metadata"][1].url;
						break;
					}
				}catch(err) {console.log(err)}
			}

			if (img_url == undefined) continue;

			add_article(article.title, article.published_date, img_url, article.abstract);
		}

		getting = false;
	}).catch(err => {
		console.log(err)
		clear_articles();
		add_article("There was an error!!", "", "", err);
		getting = false;
	})//*/
}