import {useState} from "react";
import './App.css';

export function IndividualRadio({nam, classNamei, classNamel, val, id, ttl, state, func}) { // eslint-disable-next-line
	let updateToChecked = (state == val && classNamel != null);
	let BackC = updateToChecked ? "black" : "";
	let TextC = updateToChecked ? "white" : "";
	return (<>	
		<input
			type="radio"
			className={classNamei}
			name={nam}
			value={val}
			id={id}
			checked={state === val}
			onChange={func}
		/>
		<label className={classNamel} style={{backgroundColor: BackC, color: TextC}} htmlFor={id}>{ttl}</label>
	</>)
}

export function RadioButtons({
		name, 
		func, 
		option1, 
		title1, 
		option2, 
		title2, 
		option3, 
		title3
	}) {
	const [optionType, setOption] = useState(name);

	const onOptionChange = e => {
		if (func != null) {
			func(name, e.target.value);
		}
		setOption(e.target.value);
	}

	return (<>
		<IndividualRadio nam={name} val={option1} id={option1} ttl={title1} state={optionType} func={onOptionChange}/><br/>
		<IndividualRadio nam={name} val={option2} id={option2} ttl={title2} state={optionType} func={onOptionChange}/><br/>
		<IndividualRadio nam={name} val={option3} id={option3} ttl={title3} state={optionType} func={onOptionChange}/><br/>
	</>)
}