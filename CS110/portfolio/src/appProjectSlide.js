import './SliderTemplate.css'
import './ProjectSlide.css'
import {Slide, SlideTitle} from './appSliderTemplate'

let project_list = [
	{
		title: "CS 179F Presentation",
		imgSrc: "https://henrimalahieude.github.io/img/cs179f.png",
		alt: "yt img",
		prjLink: "https://www.youtube.com/watch?v=g8IBAL2kROc",
	},

	{
		title: "CS 147 Presentation",
		imgSrc: "https://henrimalahieude.github.io/img/polyglot.png",
		alt: "Zig+Rust Logo Image",
		prjLink: "https://youtu.be/C_tbRb4xPqQ",
		gitLink: "https://github.com/HenriMalahieude/Polyglot",
	},
	{
		title: "CS 120B Presentation",
		imgSrc: "https://henrimalahieude.github.io/img/radar.png",
		alt: "arduino radar sonar",
		prjLink: "https://youtu.be/Z2UKC_wSfbI",
		gitLink: "https://github.com/HenriMalahieude/RadarModel",
	},
	{
		title: "Gravity Simulator",
		imgSrc: "https://henrimalahieude.github.io/img/gravity.png",
		alt: "gravity image",
		prjLink: "https://henrimalahieude.github.io/gravity-simulator/",
		gitLink: "https://github.com/HenriMalahieude/gravity-simulator",
	},
	{
		title: "Perlin Noise Generator (w/ Go + WASM)",
		imgSrc: "https://henrimalahieude.github.io/img/perlin.png",
		alt: "perlin image",
		prjLink: "https://henrimalahieude.github.io/GoPerlinNoise/",
		gitLink: "https://github.com/HenriMalahieude/GoPerlinNoise",
	},
	{
		title: "GoStructures Package",
		imgSrc: "https://henrimalahieude.github.io/img/bst.png",
		alt: "binary search tree",
		prjLink: "https://pkg.go.dev/github.com/HenriMalahieude/GoStructures",
		gitLink: "https://github.com/HenriMalahieude/GoStructures"
	},
	{
		title: "Chess Project",
		imgSrc: "https://henrimalahieude.github.io/img/ChessGame.png",
		alt: "Chess Game",
		prjLink: "https://henrimalahieude.github.io/Chess/",
		gitLink: "https://github.com/HenriMalahieude/Chess"
	},
	{
		title: "Maze Playground",
		imgSrc: "https://henrimalahieude.github.io/img/VisualMazeGenerator.png",
		alt: "maze",
		prjLink: "https://henrimalahieude.github.io/VisualMazeGenerator/",
		gitLink: "https://github.com/HenriMalahieude/VisualMazeGenerator"
	},
]

function ProjectElement({title, imgSrc, alt, prjLink, gitLink}) {
	return (<div className="prj-elm">
		<div className="prj-elm-top-bar">
			<h3>{title}</h3>
			{(gitLink) ? (<a href={gitLink}><img className="inverted-img" src="https://henrimalahieude.github.io/img/github.png" alt="github logo"/></a>) : (<></>)}
		</div>
		<a href={prjLink}>
			<img className="prj-img" src={imgSrc} alt={alt}/>
		</a>
	</div>)
}

export class ProjectSlide extends Slide {
	render() {
		return (<div className="slider slide3">
			<div className="slider-page">
				<SlideTitle text="Projects"/>

				<div className="proj-grid">
					{project_list.map((value) => {
						return ProjectElement(value);
					})}
				</div>
			</div>
		</div>)
	}
}