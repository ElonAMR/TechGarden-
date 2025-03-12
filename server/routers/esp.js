const express = require('express');
const router = express.Router();
const fs=require('fs');

router.get('/',(req,res)=>{
    const  {temp , light , moisture} = req.query;
    console.log("temp = "+temp + ", light = "+light +", moisture = "+moisture);
});

router.get('/state',(req,res)=>{
    let data = JSON.parse(fs.readFileSync("Inside_information.json", "utf8"));

    data.shabbat.currentTimeHour = new Date().getHours().toString();

    fs.writeFileSync("Inside_information.json", JSON.stringify(data), 'utf8');

    res.json(data.state);
});

router.get('/dataMode' ,(req, res)=>{
    const {state} = req.query;
    let data = JSON.parse(fs.readFileSync("Inside_information.json", "utf8"));
    res.json(data[state]);
})




module.exports=router;