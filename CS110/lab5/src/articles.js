import './App.css';
import {useState, useEffect} from 'react';
import {IndividualRadio} from './radioButtons.js';

const page_limit = 6;
const wait_time = 2;
const unavailable_image = "https://cdn4.iconfinder.com/data/icons/thin-gui-elements-2/24/thin-1550_website_error_missing_404-512.png";
let article_list = [];
let dbnc = Date.now(); //a debounce so that we don't go over our wait

/*for (let i = 0; i < 3; i++) {
	article_list[i] = [];
	for (let j = 0; j < page_limit; j++) {
		article_list[i][j] = {
			title: "testing (" + i + ", " + j + ")",
			date: "01-01-0101",
			abstract: "lorem ipsum",
			media:unavailable_image,
		}
	}
} // */

//console.log(article_list.length, article_list[0].length)
function Article({title, date, abstract, imgSrc}){
	return (<>
		<div className="article">
			<div className="a-meta">
				<div className="am-title">{title}</div>
				<div className="am-date">{date}</div>
			</div>
			<div className="a-details">
				{(imgSrc != null) ? <img className="ad-thumbnail" src={imgSrc} alt="article img"/> : <></>}
				<div className="ad-blurb">{abstract}</div>
			</div>
		</div>
	</>)
}

function ArticlePage({page}) {
	return (<>
		{ (article_list.length > 0 && !Number.isNaN(Number(page))) ?
		article_list[Number(page)-1].map((article, index) => {
			return <Article title={article.title} date={article.date} abstract={article.abstract} imgSrc={article.media} key={index}/>
		}) : <Article title="loading" date="00-00-0000" abstract="please wait" imgSrc={unavailable_image}/>}
	</>)
}

function PagingButtons({amount, state, func}) {
	const buttons = [];
	for (let i = 1; i < amount+1; i++) {
		buttons.push(<IndividualRadio key={i} nam="paging-radios" classNamei="pager-radios" classNamel={"pager-label"+i} val={i} id={"pagebutton"+i} ttl={i} state={state} func={func}/>);
	}

	return <>{buttons}</>
}

let getting = false;
async function GetArticles(updateCount, srtby, timeframe, cnt) {
	if (getting) return;
	getting = true;

	updateCount(0);
	article_list = [[]];

	let dif = (Date.now() - dbnc) / 1000;
	if (dif < wait_time) await new Promise(r => setTimeout(r, (wait_time - dif)*1000));
	dbnc = Date.now();

	let tfrme = 1;
	if (timeframe === "week") tfrme = 7;
	if (timeframe === "month") tfrme = 30;
	
	//get data from nyt
	const url = `https://api.nytimes.com/svc/mostpopular/v2/${srtby}/${tfrme}.json?api-key=KhwR0H4oNA4NdXgMshnf3w6jRfST7Y7J`;
	fetch(url).then(res => res.json()).then(data => {
		//console.log(data)
		let cpage = 0;
		let clmn = 0;

		for (let i = 0; i < cnt; i++) {
			if (article_list.length == cpage) article_list.push([]);

			let article = data.results[i];

			let img_url = undefined;
			if (article.media.length > 0) {
				for (let j = 0; j < article.media.length; j++) {
					try{
						if (article.media[j].type === "image") {
							if (article.media[j]["media-metadata"].length > 2) {
								img_url = article.media[j]["media-metadata"][1].url; //priority to smaller img
							} else {
								img_url = article.media[j]["media-metadata"][0].url; //otherwise try for next one
							}
							break;
						}
					}catch(err) {console.log(err)}
				}
			}

			//console.log("SO: ", cpage, ", ", clmn);
			article_list[cpage][clmn] = {
				title: article.title, 
				date: article.published_date, 
				media: img_url ? img_url : unavailable_image, 
				abstract: article.abstract
			};

			clmn++;
			if (clmn >= page_limit) {
				cpage++;
				clmn = 0;
				updateCount(article_list.length);
			}
		}
		
		getting = false;
		updateCount(article_list.length);
	}).catch(err => {
		console.log(err)
		article_list = [[]];
		article_list[0][0] = {title: "There was an error!", abstract: "Please try refreshing!", media: unavailable_image, date: "00-00-0000"};
		getting = false;
	})//*/
}

export function ArticlePager({sorting, timing, count}) {
	const [page, setPage] = useState("1");
	const [length, setArticleCount] = useState(0);
	const updatePage = e => {
		setPage(e.target.value);
	}

	useEffect(() => {
		setPage("1");
		GetArticles(setArticleCount, sorting, timing, count);
	}, [setArticleCount, sorting, timing, count]);

	return (<div className="article-page">
		<div className="article-container">
			<ArticlePage page={page}/>
		</div>
		<div className="paging-container">
			<PagingButtons amount={length} state={page} func={updatePage}/>
		</div>
	</div>)
}