const express = require('express');
const router = express.Router();


router.get('/',(res,req)=>{
    console.log(`hello elon`);
});


module.exports=router;