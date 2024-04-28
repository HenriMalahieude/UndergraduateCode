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