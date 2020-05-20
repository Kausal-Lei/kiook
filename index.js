var carQueryData = {
	"startRow": 1,
	"brandOrCarLevel": "",
	"brand": "",
	"defaultSort": "",
	"ndownPaymentStart": "",
	"ndownPaymentEnd": "",
	"nmonthlyPaymentStart": "",
	"nmonthlyPaymentEnd": "",
	"priceStart": "",
	"priceEnd": "",
	"downPaymentRatio": "",
	"downPaymentRatioList": {
		"zeropayments": "",
		"fivepayments": "",
	},
	"newCarShelf": "",
	"carRaisingWorryFree": "",
	"monthlySupplyDrop": "",
	"newEnergy": "",
	"carLevel": "",
	"carLevelList": {
		"minCar": "",
		"smallCar": "",
		"middleCar": "",
		"middleLargeCar": "",
		"suvCar": "",
		"mpvCar": "",
		"runCar": "",
	}
};	
$('.downPayment').on('click', function() {
	navSelectChangeThisCss(this, ".selecteList_downPayment", [".selecteList_month", ".selecteList_month"], [
		".monthlyInstallment", ".defaultSort"
	]);
});
$('.ndownPayment_ul li').on('click', function() {
	$(this).addClass("selected");
	$(this).siblings().removeClass("selected");
	setTimeout(function() {}, 100);
	var newData = $(this).attr("data-ndownPayment");
	carQueryData.ndownPaymentStart = newData.split("_")[0];
	carQueryData.ndownPaymentEnd = newData.split("_")[1];
	if (carQueryData.ndownPaymentEnd == "60000") {
		carQueryData.ndownPaymentEnd = "";
	};
	if (carQueryData.ndownPaymentStart == "0") {
		carQueryData.ndownPaymentStart = "";
	};
	carRenderData.ndownPayment = "首付" + $(this).text();
	var formNum = Number(carQueryData.ndownPaymentStart) / 10000;
	var toNum = Number(carQueryData.ndownPaymentEnd) / 10000;
	if (toNum == 0) {
		toNum = 6;
	};
	sliderRange1.update({
		from: formNum,
		to: toNum,
	});
	moveSliderRange1(formNum, toNum);
});
$('.monthlyInstallment').on('click', function() {
	navSelectChangeThisCss(this, ".selecteList_month", [".selecteList_downPayment", ".selecteList"], [".downPayment",
		".defaultSort"
	]);
});
$(".range_1").ionRangeSlider({
	min: 0,
	max: 12,
	from: 0,
	to: 12,
	type: 'double',
	step: 1,
	prefix: "",
	postfix: "元",
	prettify: true,
	hasGrid: true,
	onChange: function(data) {
		console.log(data)
		moveSliderRange1(data.from, data.to);
	},
});
var sliderRange1 = $(".range_1").data("ionRangeSlider");

function moveSliderRange1(leftNum, rightNum) {
	$('.bxsh').text(leftNum+'组');
}
$('.confirmButton1').on('click', function() {});
