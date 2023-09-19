import { Component, ViewEncapsulation, OnInit } from '@angular/core';
import TileLayer from 'ol/layer/Tile';
import { defaults as defaultControls, Zoom } from 'ol/control';
import OSM from 'ol/source/OSM';
import { Map, Overlay, View, Feature } from 'ol';
import { Point } from 'ol/geom';
import { Vector as VectorSource } from 'ol/source';
import { Vector as VectorLayer } from 'ol/layer';
import { Icon, Style } from 'ol/style';
import { fromLonLat } from 'ol/proj';

@Component({
	selector: 'app-root',
	templateUrl: './app.component.html',
	styleUrls: ['./app.component.scss'],
	encapsulation: ViewEncapsulation.None
})

export class AppComponent {
	title = 'map proj. with openlayers';
	coordinate = [25.586452, 45.642897];
	map!: Map;
	angle = Math.PI / 12.4;

	ngOnInit() {
		this.initializeMap();
	}

	createMap(): Map {
		return new Map({
			target: 'map',
			layers: [
				new TileLayer({
					source: new OSM(),
				}),
			],
			controls: defaultControls().extend([
				new Zoom()
			]),
			view: new View({
				center: fromLonLat(this.coordinate),
				zoom: 16,
			}),
		});
	}

	createMarkerLayer(markerSource: VectorSource): VectorLayer<VectorSource> {
		return new VectorLayer({
			source: markerSource,
		});
	}

	createMarkerFeature(markerLayer: VectorLayer<VectorSource>): Feature {
		const feature = new Feature({
			geometry: new Point(fromLonLat(this.coordinate)),
		});

		const button = document.createElement('button');
		button.id = 'marker-button';
		button.addEventListener('click', (event: Event) => {
			event.stopPropagation();
			const content = document.createElement('div');
			content.style.backgroundColor = 'white';
			content.style.border = '1px solid blue';
			content.style.padding = '0 10px';
			content.innerHTML = '<p>ăsta-i turnul alb din brașov</p>';
			const popup = new Overlay({
				element: content,
				autoPan: true,
				position: fromLonLat(this.coordinate),
			});
			this.map.addOverlay(popup);

			this.map.on('click', () => {
				popup.setPosition(undefined);
			});
		});

		const overlay = new Overlay({
			element: button,
			position: fromLonLat(this.coordinate),
			stopEvent: false,
		});
		this.map.addOverlay(overlay);

		return feature;
	}

	createMarkerStyle(): Style {
		return new Style({
			image: new Icon({
				src: 'https://openlayers.org/en/latest/examples/data/icon.png',
				anchor: [0.5, 1],
				rotateWithView: true,
				rotation: this.angle,
			}),
		});
	}

	handleButtonClick() {
		console.log('Button clicked');
	}

	initializeMap() {
		this.map = this.createMap();
		const markerSource = new VectorSource();
		const markerStyle = this.createMarkerStyle();
		const markerLayer = this.createMarkerLayer(markerSource);
		const markerFeature = this.createMarkerFeature(markerLayer);
		markerFeature.setStyle(markerStyle);
		markerSource.addFeature(markerFeature);

		this.map.addLayer(markerLayer);
	}
}
