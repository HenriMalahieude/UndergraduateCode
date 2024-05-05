import './SliderTemplate.css'
import React from 'react'

export class Slide extends React.Component {
	constructor(props) {
		super(props);

		this.state = props;
	}

	render() {
		return (
			<div className={"slider slide" + this.state.index}>
				<div className="slider-page">
					<h2>{this.state.name}</h2>
					<p style={{color: "white"}}>TODO</p>
				</div>
			</div>
		)
	}
}

export function SlideTitle({text}) {
	return (
		<div className="title-wrapper">
			<h2 className="slide-title">{text}</h2>
		</div>
	)
}

function StandardContentImage({imgLink, alt}) {
	return (<img className="std-cnt-img-wrapper" src={imgLink} alt={alt}/>);
}

function StandardContent({order, imgLink, alt, href, text}) {
	if (order === "reverse") return (
		<div className="std-content">
			<p className="std-cnt-p">
				{text}
			</p>
			<div className="std-cnt-img-wrapper">
				{(href) ? (<a href={href}><StandardContentImage imgLink={imgLink} alt={alt}/></a>) : <StandardContentImage imgLink={imgLink} alt={alt}/>}
			</div>
		</div>
	)

	return (
		<div className="std-content">
			<div className="std-cnt-img-wrapper">
				{(href) ? (<a href={href}><StandardContentImage imgLink={imgLink} alt={alt}/></a>) : <StandardContentImage imgLink={imgLink} alt={alt}/>}
			</div>
			<p className="std-cnt-p">
				{text}
			</p>
		</div>
	)
}

export class HomeSlide extends Slide {
	render() {	
		return (
			<div className={"slider slide1"}>
				<div className="slider-page">
					<SlideTitle text="Henri Malahieude"/>
					<div className="std-cnt-wrapper">
						<StandardContent 
							text={"Henri is a programmer specializing in low-level design and execution of computational systems. He's worked on a wide range of applications such as Game Development, Website, all the way to Artificial Intelligence Research!"} 
							imgLink="https://henrimalahieude.github.io/img/picofme1.jpg" 
							alt="Picture of Henri" />
						<StandardContent 
							order="reverse"
							text={"Having enjoyed programming as a hobby since 2013, Henri Malahieude has gained an extensive amount of experience as he's grown. His professional career between research, educational departments, and game studios has been summarized in this document. Just click to download!"} 
							imgLink="https://henrimalahieude.github.io/img/pdf_symbol.png" 
							href="https://henrimalahieude.github.io/pdfs/current_resume.pdf"
							alt="Pdf Symbol" />
					</div>
				</div>
			</div>
		)
	}
}

const ucr_logo = "https://upload.wikimedia.org/wikipedia/commons/thumb/2/21/UC_Riverside_Highlanders_logo.svg/1200px-UC_Riverside_Highlanders_logo.svg.png"
const go_logo = "https://www.tvusd.k12.ca.us/cms/lib/CA02208611/Centricity/Template/GlobalAssets/images///Logos/GOHS.png"
const cub_logo = "https://upload.wikimedia.org/wikipedia/en/thumb/d/d3/Colorado_Buffaloes_logo.svg/1200px-Colorado_Buffaloes_logo.svg.png"
export class EducationSlide extends Slide {
	render() {
		return (
			<div className={"slider slide2"}>
				<div className="slider-page">
					<SlideTitle text="Education"/>
					<div className="std-cnt-wrapper">
						<StandardContent
							text={"Henri's future lies with CU Boulder. He has been accepted into the PhD program of the Electrical Computation and Engineering Department, where he will be studying with Dr. Izraelevitz towards his degree."}
							imgLink={cub_logo}
							alt="CUB Logo"/>
						<StandardContent 
							order="reverse"
							text={"Arriving at UCR, he had a huge advantage compared to his peers. Many of his credits had transferred over from high school, meaning he could focus most of his energy on the major related courses of Computer Science rather than on GEs. Henri graduated on June 17th of 2024."} 
							imgLink={ucr_logo} 
							alt="UCR Logo" />
						<StandardContent 
							text={"While Henri began programming in 2013, his first formal class didn't start until he took AP Computer Science A in Junior Year of his High School career. In between those years, Henri had already learned Lua, HTML, CSS, and C++. Choosing C++ as his favorite. Though he didn't spend a lot of time on Computer Science as he had been enrolled in the IB Program."} 
							imgLink={go_logo} 
							alt="Great Oak Logo" />
					</div>
				</div>
			</div>
		)
	}
}

const scioly_logo = "https://illinoisolympiad.org/wp-content/uploads/2023/09/SO40thTranspWhite.png"
const areo_logo = "https://aerospacesystems.weebly.com/uploads/8/6/6/0/86607040/editor/logo-white.png?1515841417"
const umbra_logo = "https://se-images.campuslabs.com/clink/images/a5910702-8216-4275-b346-972b832d285dbe147c65-2fa4-46a9-abe3-b994b89868ee.png?preset=med-sq"
export class ExtracurricularSlide extends Slide {
	render() {
		return (
			<div className={"slider slide4"}>
				<div className="slider-page">
					<SlideTitle text="Extracurriculars"/>
					<div className="std-cnt-wrapper">
						<StandardContent 
							text={"In High School, Henri was a very active member within the Science Olympiad club at Great Oak. His favorite category to compete in were the 'build' events as they required he enjoyed the process of creating something more than memorizing things for the 'study' events. He frequently competed on the State Level for California, receiving many medals for his performance."} 
							imgLink={scioly_logo} 
							alt="Science Olympiad Logo" />
						<StandardContent
							text={"While Clubs have slowed down in University due to taking on a higher load of work, Henri attended the Aerospace club for about half of his time at UCR. There he designed almost all of the software for one of their ongoing projects 'Cube Satellite'."}
							imgLink={areo_logo}
							alt="Aerospace Club @ UCR Logo" />
						<StandardContent
							text={"The last Club that he participated in was the Undergraduate Missiles Ballistics and Rocketry Association at Cal Poly Pomona University. Dragged into it by his friend there, he has contributed a number of sections to the code on the avionics control board for their 'Exo Bronco' project."}
							imgLink={umbra_logo}
							alt="Umbra @ CPP Logo" />
					</div>
				</div>
			</div>
		)
	}
}