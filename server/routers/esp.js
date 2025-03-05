const express = require('express');
const router = express.Router();
const fs=require('fs');

router.get('/',(res,req)=>{
    const  {temp , light , moisture} = req.query;
    console.log("temp = "+temp + ", light = "+light +", moisture = "+moisture);
});

router.get('/state',(res,req)=>{
    let data = JSON.parse(fs.readFileSync("Inside_information.json", "utf8"));
    data={
        state:data.state,
        date:new Date().getHours()
    }
    res.JSON(data);
});

router.get('/dataMode' ,(req, res)=>{
    const {state} = req.query;
    let data = JSON.parse(fs.readFileSync("Inside_information.json", "utf8"));
    res.json(data[state]);
})




module.exports=router;