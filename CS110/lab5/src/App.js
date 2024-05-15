import './App.css';
import {useState} from 'react';
import {RadioButtons} from './radioButtons.js';
import {ArticlePager} from './articles.js';

function TopTitle({text1, text2}) {
  return (<div className="top-name">{"MOST " + text1.toLocaleUpperCase() + " - " + text2.toLocaleUpperCase()}</div>);
}

function App() {
  const [sortby, updateSortby] = useState("viewed"); 
  const [timeframe, updateTimeFrame] = useState("day");
  const [tempLimitBuffer, updateLimitBuffer] = useState(15);
  const [limit, updateArticleLimit] = useState(15);

  function updateArticles(updateType, value) {
    //console.log(updateType, ": ", value);
    if (updateType === "sortbyer") {
      updateSortby(value);
    } else if (updateType === "timeframe") {
      updateTimeFrame(value);
    } else if (updateType === "limit") {
      let lll = Number(tempLimitBuffer);

      if (Number.isNaN(lll) || lll < 1 || lll > 15) {
        alert("Invalid Article Limit.\n(Must be between 1 - 15)")
        return;
      };

      updateArticleLimit(Number(tempLimitBuffer));
    }
  }

  const updateBuffer = e => {
    updateLimitBuffer(e.target.value);
  }

  const updateLimit = e => {
    updateArticles("limit", e.target.value);
  }

  return (<>
    <TopTitle text1={sortby} text2={timeframe}/>
    <div className="total-container">
      <div className="filter-container">
        <div className="fc-title">Filters:</div>
        <div className="fc-theme">
          <div className="fct-title">Article Limit:</div>
          <input type="text" id="article-limit" name="article-limit" placeholder="1-15" onChange={updateBuffer}/>
          <input type="button" id="al-confirm" name="al-button" value="Confirm" onClick={updateLimit}/>
        </div>
        <div className="fc-theme">
          <div className="fct-title">Sort By:</div>
          <RadioButtons name="sortbyer" func={updateArticles} 
            option1="viewed" title1="Most Viewed"
            option2="shared" title2="Most Shared"
            option3="emailed" title3="Most Emailed"/>
        </div>
        <div className="fc-theme">
          <div className="fct-title">Time Frame:</div>
          <RadioButtons name="timeframe" func={updateArticles} 
            option1="day" title1="Day"
            option2="week" title2="Week"
            option3="month" title3="Month"/>
        </div>
      </div>

      <ArticlePager sorting={sortby} timing={timeframe} count={limit}/>
    </div>
  </>);
}

export default App;
