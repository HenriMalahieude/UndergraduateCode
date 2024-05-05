import './App.css'
import * as nvbr from './appNavBar'
import {EducationSlide, ExtracurricularSlide, HomeSlide} from './appSliderTemplate'
import {ProjectSlide} from './appProjectSlide'

export default function App() {
  return (
    <div className="app-content">
      {nvbr.NavBar()}
      <HomeSlide />
      <EducationSlide />
      <ProjectSlide />
      <ExtracurricularSlide />

      <div className="footer">
        <p>Henri Malahieude</p>
        <p>henrimalahieude@gmail.com</p>
        <a href="https://github.com/HenriMalahieude">github.com/HenriMalahieude</a>
        <a href="https://www.linkedin.com/in/henri-malahieude/">linkedin.com/in/henri-malahieude/</a>
      </div>
    </div>
  );
}
