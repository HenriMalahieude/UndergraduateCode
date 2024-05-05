import {useState} from "react";
import './NavBar.css';
import {FontAwesomeIcon} from '@fortawesome/react-fontawesome';
import {faHouse, faCode, faMedal, faPen} from '@fortawesome/free-solid-svg-icons';

let slides = ["Home", "Education", "Projects", "Extracurriculars"];
let slideIcons = [faHouse, faPen, faCode, faMedal];

function NavRadio() {
  const [pageInd, setPageInd] = useState("Medium")

  const onOptionChange = e => {
    setPageInd(e.target.value)
  }

  return (
	<>
      <input
        type="radio"
        name="sliders"
		    className="radio-slide1"
        value="1"
		    id="slider_1"
        checked={pageInd === "1"}
        onChange={onOptionChange}
      />

      <input
        type="radio"
		    className="radio-slide2"
        name="sliders"
        value="2"
		    id="slider_2"
        checked={pageInd === "2"}
        onChange={onOptionChange}
      />

      <input
        type="radio"
		    className="radio-slide3"
        name="sliders"
        value="3"
        id="slider_3"
        checked={pageInd === "3"}
        onChange={onOptionChange}
      />

      <input
        type="radio"
		    className="radio-slide4"
        name="sliders"
        value="4"
        id="slider_4"
        checked={pageInd === "4"}
        onChange={onOptionChange}
      />

    </>
  )
  ////{(pageInd == 1) ? (<div className="FUcl 1"></div>) : ((pageInd == 2) ? (<div className="Fuck 2"/>) : ((pageInd == 3) ? (<div className="Fuck 3"/>) : (<div></div>)))}
}

function NavSymbolButtons({value, index}) {
	return (<>
		<label key={index*5} htmlFor={"slider_"+index} className={"page"+index+" nav-desktop"}>{value.toLocaleUpperCase()}</label>
		<label key={index*7} htmlFor={"slider_"+index} className={"page"+index+" nav-mobile"}><FontAwesomeIcon icon={slideIcons[index-1]}/></label>
	</>)
}

export function NavBar() {
	return (
		<>
		<NavRadio/>
		<nav className="nav-pages">
			{slides.map((value, index) => <NavSymbolButtons key={index} value={value} index={index+1}/>)}
		</nav>
		</>
	)
}