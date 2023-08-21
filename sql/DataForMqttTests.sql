DELETE FROM `supla_client`;
DELETE FROM `supla_scene_operation`;
DELETE FROM `supla_scene`;
DELETE FROM `supla_rel_cg`;
DELETE FROM `supla_dev_channel_group`;
DELETE FROM `supla_dev_channel`;
DELETE FROM `supla_iodevice`;
DELETE FROM `supla_rel_aidloc`;
DELETE FROM `supla_location`;
DELETE FROM `supla_accessid`;
DELETE FROM `supla_user`;

INSERT INTO `supla_user` (`id`, `short_unique_id`, `long_unique_id`, `salt`, `email`, `password`, `enabled`, `reg_date`, `token`, `password_requested_at`, `limit_aid`, `limit_loc`, `limit_iodev`, `limit_client`, `timezone`, `limit_schedule`, `legacy_password`, `iodevice_reg_enabled`, `client_reg_enabled`, `limit_channel_group`, `limit_channel_per_group`, `rules_agreement`, `cookies_agreement`, `oauth_compat_username`, `oauth_compat_password`, `limit_direct_link`, `limit_oauth_client`, `locale`, `account_removal_requested_at`, `api_rate_limit`, `mqtt_broker_enabled`, `mqtt_broker_auth_password`, `home_latitude`, `home_longitude`) VALUES
(48, '8ce92cb8c9f6db6b65703d2703691700', '7398ff8ec8bed5f2c340d4d9b869f8bcb28810f2b289662c8c26814fb51580d2f2cdcbc0c5e39085ebb2cbc0233b55fe40d2d4b48e3b495dbb0bd8b608b218c777bb9bc0be5bb3f479050320f7e39c199d86bf9b4d88866b1c1bbd246230ebcbf27698d3', '48', '48test@supla.org', '$2y$13$73/pyNuKBJ2ZBFY21bI36Ouyoy5EpqMBhgu/G3KnuyDIPtrFuT8tm', 1, '2019-07-05 16:10:56', '', NULL, 10, 10, 100, 200, 'Europe/Rome', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'it', NULL, NULL, 1, NULL, 0, 0),
(53, '61b2f9bdb22d3bd6336bb235bcb1b77e', '9cbfbe6fbfce6fb1b77beccbc1ec56d7637ebdb866be425811b0c08e31b831db297272cc6bd476200ddbec088ee12f2f1e5c7c6e6f942345b2bb2f72717390f0847d3290cdc362ebfb39dff09f3d0bd57bb04b36f4c3f112bb0cbb7e4f89dc70b0c76370', '53', '53test@supla.org', '$2y$13$2emVQPeWR.b0zwDVhfgqC.yxQItD8hNXvQnlz.ex3Vb4uIYqIH0eK', 1, '2019-07-05 16:52:53', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(117, '5b15b00055c044220196eb41965b3627', '894bfe5787d3ff450bbe9b3b67d7cb4b2e540fc3b252b7b3965594230b2e3f7f475337861b094e2e8459620d3b8923d9f639f77008b73d0d0dfef9d5d678142bbb4250966e4fb4b9d0b8e0fdbbb48e0c07d4fde78fb540efe999e91388c4b7ffd43134e1', '117', '117test@supla.org', '$2y$13$xQq/TYfnHkHNOXVbxgYXfeHvSugqnX1mTAtUf4J8BIrUBNz1GzLMG', 1, '2019-07-07 16:39:58', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(121, '45004b208185b207175522c7471f8526', '79b9c6e90e0bdc832df2de5276cc3082d6ef04b2249f59567fff6cd6f82e2b3039bfb784c394db7b8bef615192c35020b4c7def5b56e7791b5b59be661b81e8e73dbf130d1bc549e891bbe595f0b60cf064b4ece83b690f0fb6d168567d04e36431f15c1', '121', '121test@supla.org', '$2y$13$jSoobKktC0Xky/DvpNIHL.IATcOSW7QkgBYctIMfdf06Ybj8kuE72', 1, '2019-07-07 17:51:59', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(171, '0c6beb47b1c2b14191e2bbb49e9d41c2', '34f8d335183be00d95731ce8b129fc07bb3d669b6b9f1e3ffc4ebf63cfddf8b618e99f391263bbcb75d8fc2715b7b6281213169f55c4c9fc819269685c078fb17dd23c7f93527b4243e7b6c2c250b39f1f5ebb0bf327f908628382d0b71902e6e838bbeb', '171', '171test@supla.org', '$2y$13$Aolx.Q12J0FFGRBb2MhY0O57O73urWN4HooYlSDVBoPxGGew6UCFb', 1, '2019-07-09 13:34:06', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, '2020-11-17 14:43:34', NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(239, '4d3e49b9f3b202b1092fbfdc48d8d04f', '4d7bfc98d1fbdf77089defb20be077b9284099708bb9b1e241cb6ebc559019ee4ee6dd953b13b27b20dd2f958bd3f7cfbdbdb86fdf965e8c75f87473c3b00dd6b36306cc07ef3714c7db6037cd7f12646dceb61b437bc8d1fcb1bf5d0b525552505cddb4', '239', '239test@supla.org', '$2y$13$nORg3up1mXWpux.vKXbA9ur/.2AokHQ1AvNPW/s6PI9juwiQQcZkC', 1, '2019-07-11 10:23:29', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(390, 'de1257b7824b6825c276b763db1b711f', '164e5bdc381c9bb8b449e7b49eb6567b3c4608069bdbc68b57424e246468b2f31fb90657f06dbf3c4d920d9864bc522b4c4c412f2f5ebc660b2c8d4c792bf2efcbf3fb3675810c84d2eb64787c49536677e02bf680724b890f237cfe58312b5c49494ef3', '390', '390test@supla.org', '$2y$13$he6drSdX6XOt9cT7jH75JupqsCPopHIr/7wo0eAoxl5kjXfft0yk.', 1, '2019-07-15 13:25:36', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(431, 'b72dfbdb402908e6939d7257dfed2367', 'bcdc0e9035802478e707b7b0259294d61307bfd7c8b01681d005d8366334eb54908b02f12ed8fbde1b5b4c660d36d81f7587b88601324ffbfcfce7ed49e627553203cd104d98558e31b6d418548390f8d25e41e39e6098bb4e9421e4e889f9bf3d9b1044', '431', '431test@supla.org', '$2y$13$TnxiY8VXNxubM084KwlJ8u/.tTYw/Gl4GeVKC.o9u5OOmXKHQEw3y', 1, '2019-07-17 08:41:40', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, '1500/3600', 1, NULL, 0, 0),
(632, '3281677315ff159f91471b34828f603b', '7dbb7b697de609198e7ec76b9c00983222751dbe127c09de6091131b88248d99c50d82fc8ce0944939197bc9d79ed4cdb9ff841003cf7d2433b29bcf8ffc4e0cb808580eddcc9f7662f5bbcfd815f71c2e6fce060db9ebcb743c3304cd62f40be3917214', '632', '632test@supla.org', '$2y$13$GAqbEreoDt6yjv3QGJgOy.A1PuO9gNgBjRMUE5pGUnIOsWnObDxBK', 1, '2019-07-23 08:18:19', '', NULL, 10, 10, 100, 200, 'Europe/Paris', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(676, '46948d474db1b5e3cccf2c89281414c2', '0e7bef1e2d99728dbb97fb8738c4c04ddf67293f3edd41973bd8eb214bb9f6053e6be3262fbc6b9d2e8981de4c0d9634b82691b564bf5b21ee383dfdeb967bcc8c5eb5d5ce5b02bfdd2ccbc46d66494fbb1f8b04ee9083c148107b28bb796292397063b5', '676', '676test@supla.org', '$2y$13$Arv/CtxV1Kh4b7MWQrjjoeYWlQj7Xc7qgmK7.sSCYGBzhIbAsIi9b', 1, '2019-07-23 16:36:36', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(743, '0df527b1786040fe57d6d9f43b632fbb', '23e3b866b60393543896f03dd38799e6b93f861307f23e4d52589e8b66314bd0b15c0bbdbddd1479c7b206b00f5fb81919bb5d93d7769f3ceeebdc68e3be1b166c2d610709d9c2c28143fbd6c9953823ed9dffd697319b9cc7b21c2b163f68e208d94519', '743', '743test@supla.org', '$2y$13$WeLLd0IsXCjDT.qHV2tV/OOincjlZVCJDxpCxOZ5hLPi605HNdcHu', 1, '2019-07-25 17:44:03', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1009, 'c2e6c948d570bfb4e8b7152d890937db', '09bb9b6e60b5fec2e2b15247862ded4d7393b3c3763f1d6584151bb50287bbe7312f99d62b6f877ebdbd5cb40632297bb1890e16230b1b0beec0c497e95de94d37d8ee3c03e683e0755081d866e1e9f9c515947681fb19276382b2dedf9bcfbb1d201414', '1009', '1009test@supla.org', '$2y$13$FN0R7clcG9VzfEbK8/bUbe7b/WFkqbqK/3tb2l3LAjeVOf4ggTZFC', 1, '2019-08-01 12:19:26', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1017, '8588fb099c7f6f32d0b5dc43cbc3318b', 'c5e215ff7261bf80140f10dcf046b4db7d8bb04b56846e0ef859f7ffb93521cdc1147282228f051db51cbdcbe6e96be755374228912520c2eb2ec147f72ef254d94b3395921b8d73bb9294b97e17e9040825f097cb8fdf8819eb72ec97dbc0ef7be73116', '1017', '1017test@supla.org', '$2y$13$/YdqWSCSVL/LZZcpRpD4JO0KrKBFx.ez1KGlA7lo7.UNZjKd7BkW.', 1, '2019-08-01 13:23:53', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1238, '7450214b8189dc129301c2c922cdcfd0', '5799b5391f21784979ce54bbe6bec65857cc38b32bc79efbe50b4ff4eb9332fbc179c733cd81bbe16becd9689b81b66fe62bb00148127bd76c47d193d5527ec9403d95e23ec91db7bc64e872d749dcd8bc9dd127b677b83360bb05c3bc2c868bbdebe127', '1238', '1238test@supla.org', '$2y$13$Q5ub7J3LA4oqRUz9MiChIeISck0S.mL/kpES1.mnuMD1YArSMf9jm', 1, '2019-08-07 10:52:38', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'en', NULL, NULL, 1, NULL, 0, 0),
(1347, 'bd6287c398bc81403c643410f5043d4e', '47d5113053f34cb9fb924ddbe8b195585bbbff372594780bdc864db7980c6beec933bd9f5cf5bfe6ebc32be1d3381d0206f4fbf4306b33b6b5f5c4f1fe4b22cff0f2f314350eb345c5b336e433dce0058786b03de38de31ccb9b2df325987313e40bf683', '1347', '1347test@supla.org', '$2y$13$TzvTg6puvPMUo66OZIr/heM/g1MO7C0TzTcfsLMoUZp7VVojm5Lhu', 1, '2019-08-09 17:12:13', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1414, '689eb3922683b4e4e7b9227f32f2d89b', '40159196991fb39058063eb8de64be00fe4c59659137ff280c16b155b6fd914c96fb890405b18bb6ebc96f0d38b46bb1cd74ef29415b93b2eb094792fb7c7b8311742934f4b4b7b25bc849fcfd9e37df37becbb5797b0446b7e16cbd8ce29c7bff12572d', '1414', '1414test@supla.org', '$2y$13$BtRdgTxTlG6cn8VI.kybme6Vy1m0Z7Sw.b/COGTmt15oQYd.1hVpb', 1, '2019-08-11 18:53:50', '', NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1495, '113fb17f5b300bfbbfb667eb6d4d1ef8', '840238d73b20594be0fc7036308209938386790d837b2361dc71c896b1f369716eb9eb76ccc89bdc53206d76b8e507bfbbce649b73e6f3336816180cc1c358d60b37cb4147bb624629c6703d964df59bb433c2fb93378fbd0802b6d0cbb5779c18fb67f3', '1495', '1495test@supla.org', '$2y$13$PY14Nscg6uzRnQ.kU4JjueIHX04ZR2wtN7uDIXEg8Sxlrys3D6H5K', 1, '2019-08-13 20:10:04', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1645, '1d43b8d35e31f1508c70b9b77e03e293', '4582528361d1e0e21e19442938f21b14982f5e3f178e026d6b1b24bf5d7309103e3f14741f54deb963c01433b2bf9306b6b46bf15cbb56b0077c81def22b7b3bf3ed9e18b1354697275c38f2c55361942f2b3b0e44869d8710e6b4509e055d40b9bbff1e', '1645', '1645test@supla.org', '$2y$13$67xwBQw87wAbufF1VWmG/OKY/1k5fnMbwN.0vjADO3k2TMdwJ.fU.', 1, '2019-08-19 08:23:53', '', NULL, 10, 10, 100, 200, 'Europe/Budapest', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1792, 'b9802383dd06c57d0c41de6805957d0f', 'b8b20bb8e2674ccb8423365be7b98dc149bcf95b035cbe78e33e84023bfe097e13b919e54122eccd46c608bc406d3734833ee2e6123bc7359d8fb398db0b8263d827cf5fe855870879c65b4b03341b74639c9b8f52b80492775b10f882284224b63d43d1', '1792', '1792test@supla.org', '$2y$13$j8Yiym.zNoeNNiMKh.Q7.O46tG4RIwCHJUo.bbk2DGJPQS/84vrmu', 1, '2019-08-23 10:04:38', NULL, NULL, 10, 10, 100, 200, 'Europe/Prague', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'cs', NULL, NULL, 1, NULL, 0, 0),
(1802, '64d3d5bd59eb5fe2b67bf4fe4d222905', 'e1d006203bb405eb1586310c8783670b7312109c47bfc82091cb29f2f85bdcbf1b86ee545d9b356f8939ed2249669c18e2c164f45832810d3e3b92373442f9b79c5e2eb1eb638508ef20f5e84f6bcff81d84bb0925847c7879b0ef3b1b684e34c3299b7d', '1802', '1802test@supla.org', '$2y$13$cxOmJq9JkpUjHQAbckCAk.oEWWgITe/5WIUcGQkbtuewHvJqLipsK', 1, '2019-08-23 12:01:43', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1840, '93158d9b795bb1c65e79199d42381706', '7c2bd95f56d0184962d8b6ec3627edc64ffbf6f62fff20b3b66ddebbd7929b3e207355b9b34ce0f1b6ec80f49b48733e7ed6dbcd2f210dc463685801c35df8273163b2ecbd87c1ecb93c83fd099089ceb8d3802cd1874d88c1b1c256566b73892b334761', '1840', '1840test@supla.org', '$2y$13$4Lc1ul.r/zkAZTUgLot1BOZnN6JXgwgXbHCKmh.eZp7IVOT8R0duu', 1, '2019-08-23 20:00:19', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(1899, '4b2bb30d2db31cf5809ede445862f6d7', '5547c2f8f1ed51b0c221bf9bfe5d282f2bb3b8c953de0fd2c0b1bfb229e371443d365bfb6d1b273de8f8f90e92b19dc87e32cb8bb04e910d34bc876fc305679bbbd55ce19e1b8713db96f92b61179ef4272898d9e6cf243184f28793dfd7256b4e51db11', '1899', '1899test@supla.org', '$2y$13$/A6mRFMvCdC5HeHo/7ny8ubmSQOlyXYbRijhqt7cxgYvE/LfMr5O6', 1, '2019-08-25 19:27:40', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(2288, '879b9d8688bc4b7108801c5c6bff4b3b', '4609db8d601bbf7c273cee4400dfd784b136b469ccd6d2620d38f19fb46de5b22cf0e3253f79d69c422cc064fd8b999e734bd7be44706d4553d5b1b153c4f4707e862bf974f3c18bfb00eb4629f4154016df3bb202cf6bb37b5ec063173bbbe1964fdbbf', '2288', '2288test@supla.org', '$2y$13$3dAlNNlu3Ij1Tg4ekv/hZuI0sRkpANVqBwnmBf21DSFLjXTy7see.', 1, '2019-09-03 17:43:40', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(2337, 'ee2611c4632f53261cf3fb8d9d2f182d', 'b33b1f4c87c827cddb348e17b0222224bdb2922ee85d698ece485896cb290b15cdb2b798c9852f6994109fdb5cf4e4d879d4b4611fb7590b285736318bdd062be0574e64f93ce11540c7ccc28cb4558400bc30cb56213149785bec1d9b853b146f43de4c', '2337', '2337test@supla.org', '$2y$13$NrMRc5R41kYqQxPgXzGUF.lgA310NEISWiA.Cchp7m9/THphchA9W', 1, '2019-09-05 10:39:00', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(2487, '7e2182788b9214ee5b66349d5b7668cf', '099d892cdedbb764c4389c0b6147b301cfeb05f6bd1f50de381c20b24048499b787d6b2920b3e098c92b90584b33f88bc5e596418b1b915d73391e8ee04076ee5b10b61b1915c70e02d2030e3e69dff078d946e117bc2c79e51ed1c6bb830b9b5d4db565', '2487', '2487test@supla.org', '$2y$13$PCNFfGFp4/hwGjufIE7OLec5B/bIRgrTG/rpX2TY5WZWlILbQD6Nm', 1, '2019-09-09 07:35:03', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(2645, '6527881802ebd8c4ff2b3955bc326704', '910e954de49f6e7f63b8350df51ecb7de87b185b86c9b791fdc8f544ff7e4b30411d0b05001b44157d5587cde22915b78bb421e70bbc3cc20bfb891bfdc0c8c9bbb3c317984cd957d2d22d5c8c3140f052175db6b645bbeb97472cbb5fb5d5eb6171ce77', '2645', '2645test@supla.org', '$2y$13$BezpDGH.ni3mIJTb6WlJbu3Ssj/OLLTV8WW0t3AOgLWI3UbOUfmAW', 1, '2019-09-13 12:06:18', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(3411, '15cb17b568de00e1ddc3005e4674bbde', '7e7bffb91c5cdf6bcc2fd042b36e8b4c21cb98b645db4bb8e30ccb4f7bcf202f43e5e15bbbe3f27f5349341853bb03dd14d960cd6b1df6b249f63bc8312360c48bfc4909c44c37d51dd3b89bf7e464bb722b58cbf5e2cc5c06ff87dc433241b80f7b8080', '3411', '3411test@supla.org', '$2y$13$lPEUHbcklqlbGmvqM40k3eVZ4XvyRIvrIXeilYV.AK5kbBffFk3QK', 1, '2019-10-02 22:48:04', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(3741, 'c8e5fd3b528033b98e09e0d1582d1031', '2b7811c1bbbdbb90e845de009c818d8909b383799bb8e19879f0f61207b78f498827b82b8dfe9cd55b1bce8ee4bfb2cdfb2774ebd0b138b142cbe85f559b164d12c96d4e7bfb412b82f63f0939b8c4b96f0f2342fcb0c5264697dbc53e09607cbbe96604', '3741', '3741test@supla.org', '$2y$13$iuhHKeV0wwKLhw.JAT941eHKS6j/Ft.3JW4SLT34yJ8RvrQ6nOoJG', 1, '2019-10-09 10:12:02', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0),
(3748, 'aae5fd3b528033b98e09e0d1582d1031', 'bb7811c1bbbdbb90e845de009c818d8909b383799bb8e19879f0f61207b78f498827b82b8dfe9cd55b1bce8ee4bfb2cdfb2774ebd0b138b142cbe85f559b164d12c96d4e7bfb412b82f63f0939b8c4b96f0f2342fcb0c5264697dbc53e09607cbbe96604', '3748', '3748test@supla.org', '$2y$13$iuhHKeV0wwKLhw.JAT941eHKS6j/Ft.3JW4SLT34yJ8RvrQ6nOoJG', 1, '2019-10-09 10:12:02', NULL, NULL, 10, 10, 100, 200, 'Europe/Warsaw', 20, NULL, NULL, NULL, 20, 10, 1, 1, NULL, NULL, 50, 20, 'pl', NULL, NULL, 1, NULL, 0, 0);

INSERT INTO `supla_accessid` (`id`, `user_id`, `password`, `caption`, `enabled`) VALUES
(44, 48, '***', 'Access Identifier #1', 1),
(50, 53, '***', 'Access Identifier #1', 1),
(123, 117, '***', 'Access Identifier #1', 1),
(127, 117, '***', 'Access Identifier #2', 1),
(128, 117, '***', 'Access Identifier #3', 1),
(130, 121, '***', 'Access Identifier #1', 1),
(178, 171, '***', 'Access Identifier #1', 1),
(252, 239, '***', 'Access Identifier #1', 1),
(401, 390, '***', 'Access Identifier #1', 1),
(458, 431, '***', 'Access Identifier #1', 1),
(667, 632, '***', 'Access Identifier #1', 1),
(724, 676, '***', 'Access Identifier #1', 1),
(811, 743, '***', 'Access Identifier #1', 1),
(1096, 1009, '***', 'Access Identifier #1', 1),
(1104, 1017, '***', 'Access Identifier #1', 1),
(1354, 1238, '***', 'Access Identifier #1', 1),
(1468, 1347, '***', 'Access Identifier #1', 1),
(1519, 239, '***', 'Access Identifier #1', 1),
(1536, 1414, '***', 'Access Identifier #1', 1),
(1647, 1495, '***', 'Access Identifier #1', 1),
(1819, 1645, '***', 'Access Identifier #1', 1),
(2010, 1792, '***', 'Access Identifier #1', 1),
(2021, 1802, '***', 'Access Identifier #1', 1),
(2062, 1840, '***', 'Access Identifier #1', 1),
(2128, 1899, '***', 'Access Identifier #1', 1),
(2528, 431, '***', 'Access Identifier #1', 1),
(2599, 2288, '***', 'Access Identifier #1', 1),
(2648, 2337, '***', 'Access Identifier #1', 1),
(2831, 2487, '***', 'Access Identifier #1', 1),
(2996, 2645, '***', 'Access Identifier #1', 1),
(3891, 3411, '***', 'Access Identifier #1', 1),
(4260, 3741, '***', 'Access Identifier #1', 1),
(5023, 1840, '***', 'Access Identifier #2', 1),
(5024, 1840, '***', 'Access Identifier #3', 1),
(5025, 1840, '***', 'Access Identifier #4', 1),
(5276, 1347, '***', 'Access Identifier #1', 1),
(5282, 2487, '***', 'Access Identifier #2', 1),
(5316, 1009, '***', 'Access Identifier #2', 1),
(5317, 1009, '***', 'Access Identifier #3', 1),
(5318, 1009, '***', 'Access Identifier #4', 1),
(5319, 1009, '***', 'Access Identifier #5', 1),
(5320, 1009, '***', 'Access Identifier #6', 1),
(5321, 1009, '***', 'Access Identifier #7', 1),
(5322, 1009, '***', 'Access Identifier #8', 1),
(5323, 1009, '***', 'Access Identifier #9', 1),
(5467, 1802, '***', 'Access Identifier #1', 1),
(5468, 1802, '***', 'Access Identifier #1', 1),
(5667, 1840, '***', 'Access Identifier #5', 1),
(5728, 1792, '***', 'Access Identifier #1', 1);

INSERT INTO `supla_location` (`id`, `user_id`, `password`, `caption`, `enabled`) VALUES
(44, 48, '***', 'Location #1', 1),
(50, 53, '***', 'Location #1', 1),
(111, 117, '***', 'Location #1', 1),
(118, 121, '***', 'Location #1', 1),
(170, 171, '***', 'Location #1', 1),
(246, 239, '***', 'Location #1', 1),
(409, 390, '***', 'Location #1', 1),
(458, 431, '***', 'Location #1', 1),
(677, 632, '***', 'Location #1', 1),
(724, 676, '***', 'Location #1', 1),
(787, 743, '***', 'Location #1', 1),
(1091, 1009, '***', 'Location #1', 1),
(1102, 1017, '***', 'Location #1', 1),
(1329, 1238, '***', 'Location #1', 1),
(1444, 1347, '***', 'Location #1', 1),
(1460, 1009, '***', 'Location #1', 1),
(1512, 239, '***', 'Location #1', 1),
(1523, 1009, '***', 'Location #1', 1),
(1530, 1414, '***', 'Location #1', 1),
(1623, 1495, '***', 'Location #1', 1),
(1683, 1009, '***', 'Location #1', 1),
(1819, 1645, '***', 'Location #1', 1),
(2000, 1792, '***', 'Location #1', 1),
(2010, 1802, '***', 'Location #1', 1),
(2052, 1840, '***', 'Location #1', 1),
(2081, 1792, '***', 'Location #1', 1),
(2126, 1899, '***', 'Location #1', 1),
(2143, 431, '***', 'Location #1', 1),
(2151, 431, '***', 'Location #1', 1),
(2585, 2288, '***', 'Location #1', 1),
(2643, 2337, '***', 'Location #1', 1),
(2887, 2288, '***', 'Location #1', 1),
(2999, 2645, '***', 'Location #1', 1),
(3171, 1238, '***', 'Location #1', 1),
(3229, 2487, '***', 'Location #1', 1),
(3884, 1792, '***', 'Location #1', 1),
(3885, 1792, '***', 'Location #1', 1),
(3935, 3411, '***', 'Location #1', 1),
(4339, 3741, '***', 'Location #1', 1),
(4551, 53, '***', 'Location #1', 1),
(4552, 53, '***', 'Location #1', 1),
(4558, 2487, '***', 'Location #1', 1),
(4940, 1017, '***', 'Location #1', 1),
(4994, 1238, '***', 'Location #1', 1),
(5108, 3411, '***', 'Location #1', 1),
(5109, 3411, '***', 'Location #1', 1),
(5110, 3411, '***', 'Location #1', 1),
(5111, 3411, '***', 'Location #1', 1),
(5112, 3411, '***', 'Location #1', 1),
(5120, 3411, '***', 'Location #1', 1),
(5172, 3411, '***', 'Location #1', 1),
(5174, 1347, '***', 'Location #1', 1),
(5183, 2487, '***', 'Location #1', 1),
(5292, 1347, '***', 'Location #1', 1),
(5313, 1840, '***', 'Location #1', 1),
(5320, 1347, '***', 'Location #1', 1),
(5326, 171, '***', 'Location #1', 1),
(5341, 1792, '***', 'Location #1', 1),
(5342, 1792, '***', 'Location #1', 1),
(5343, 1792, '***', 'Location #1', 1),
(5344, 1792, '***', 'Location #1', 1),
(5351, 1802, '***', 'Location #1', 1),
(5413, 171, '***', 'Location #1', 1),
(5415, 3411, '***', 'Location #1', 1),
(5416, 171, '***', 'Location #1', 1),
(5422, 1802, '***', 'Location #1', 1),
(5427, 171, '***', 'Location #1', 1),
(5428, 171, '***', 'Location #1', 1),
(5429, 171, '***', 'Location #1', 1),
(5446, 1802, '***', 'Location #1', 1),
(5456, 3411, '***', 'Location #1', 1),
(5465, 1802, '***', 'Location #1', 1),
(5515, 1802, '***', 'Location #1', 1),
(5517, 1802, '***', 'Location #1', 1),
(5612, 2487, '***', 'Location #1', 1);

INSERT INTO `supla_rel_aidloc` (`access_id`, `location_id`) VALUES
(44, 44),
(50, 50),
(123, 111),
(130, 118),
(178, 170),
(252, 246),
(1519, 246),
(401, 409),
(458, 458),
(2528, 458),
(667, 677),
(724, 724),
(811, 787),
(1096, 1091),
(1104, 1102),
(1354, 1329),
(1468, 1444),
(5276, 1444),
(1096, 1460),
(1519, 1512),
(1096, 1523),
(1536, 1530),
(1647, 1623),
(1096, 1683),
(1819, 1819),
(2010, 2000),
(2021, 2010),
(5467, 2010),
(5468, 2010),
(2062, 2052),
(2010, 2081),
(2128, 2126),
(458, 2143),
(2528, 2143),
(458, 2151),
(2528, 2151),
(2599, 2585),
(2648, 2643),
(2599, 2887),
(2996, 2999),
(1354, 3171),
(2831, 3229),
(2010, 3884),
(2010, 3885),
(3891, 3935),
(4260, 4339),
(50, 4551),
(50, 4552),
(2831, 4558),
(1104, 4940),
(1354, 4994),
(3891, 5108),
(3891, 5109),
(3891, 5110),
(3891, 5111),
(3891, 5112),
(3891, 5120),
(3891, 5172),
(1468, 5174),
(2831, 5183),
(1468, 5292),
(2062, 5313),
(1468, 5320),
(178, 5326),
(2010, 5341),
(2010, 5342),
(2010, 5343),
(2010, 5344),
(2021, 5351),
(5468, 5351),
(178, 5413),
(3891, 5415),
(178, 5416),
(2021, 5422),
(5468, 5422),
(178, 5427),
(178, 5428),
(178, 5429),
(2021, 5446),
(5467, 5446),
(5468, 5446),
(3891, 5456),
(2021, 5465),
(2021, 5515),
(5467, 5515),
(5468, 5515),
(2021, 5517),
(2831, 5612);

INSERT INTO `supla_iodevice` (`id`, `location_id`, `name`, `enabled`, `comment`, `reg_date`, `last_connected`, `user_id`, `reg_ipv4`, `last_ipv4`, `guid`, `software_version`, `protocol_version`, `original_location_id`, `auth_key`, `flags`, `manufacturer_id`, `product_id`) VALUES
(12, 44, 'ZAMEL SRW-01', 1, NULL, '2019-07-05 16:38:54', '2019-09-13 13:42:00', 48, 1053069194, 1053069194, 0x5c01d1cfb916cfc762d157155aae6345, '2.7.2', 7, NULL, '$2a$04$ZgUZuVuVFPkp3Gpzq6G2p.f1F1miyA3zeC3USTmb.tIRNc.f.nqwq', 0, 4, 0),
(14, 50, 'SONOFF-DS18B20', 1, NULL, '2019-07-05 16:59:44', '2020-11-16 13:25:47', 53, 1539346732, 1539346732, 0xd128d5cdbbf8e102fe5912f8bc12034d, '2.5.3', 7, NULL, '$2a$04$77PiUEYKoefdpODqDMrx8.XRpYT5bYgkl5j.nPxTY6q8uDjuHIv8S', 0, 6, 0),
(36, 111, 'ZAMEL ROW-02', 1, NULL, '2019-07-07 17:11:39', '2020-11-13 18:04:10', 117, 3647032662, 2989165650, 0xecefbdc757be5fb715cf375f5e7ceff3, '2.7.0', 9, NULL, '$2a$04$JRPRkV2cZQEj.j8mANE8keq1BWtafn5BBBngDWa0QbyFW.UhnvIGm', 0, 4, 0),
(40, 118, 'SONOFF-TH16', 1, NULL, '2019-07-07 18:11:41', '2019-09-17 16:33:44', 121, 95256713, 95260899, 0xe30b25af1b262c9a489e4fc4e16a448f, '2.5.3', 7, NULL, '$2a$04$4RvaRAZAbK.OyQNFzH2/QuGnqhrESzCqBXTo4qcpYxbS.NF0z2b62', 0, 6, 0),
(157, 170, 'ZAMEL SBW-01', 1, NULL, '2019-07-12 17:36:07', '2020-11-16 15:03:18', 171, 776821002, 1299205758, 0xed27c85ff2a66f6bb147eb0f7ef4f8bf, '2.7.0', 9, NULL, '$2a$04$3GREMhaNWQdidxcnD8PyMONByXtYhVvF1oRXB.jtaD5lNFtQS1Lve', 0, 4, 0),
(205, 409, 'SUPLA-GATE-MODULE', 1, NULL, '2019-07-15 13:37:52', '2020-11-13 07:18:34', 390, 1392685955, 1393960571, 0x74bc33bb188fe6578b471c1bb9068cdf, '2.5.5', 7, NULL, '$2a$04$.N3EUH1qAPJwDfWm9YZSh.o2xHRGDEtx4d8E3rP1UaiumyNn3kLhG', 0, 0, 0),
(411, 724, 'ZAMEL SLW-02', 1, NULL, '2019-07-23 16:38:35', '2020-11-14 03:45:14', 676, 3113821103, 3113820977, 0x6f4665e7e6b3ed0206d9b51cdebbdbd8, '2.7.2', 7, NULL, '$2a$04$m2dp.6oWNP00t3Jw3aZSwO74ANTVWh6zRBOPejuqYYYF5Sd7BNYJa', 0, 4, 0),
(506, 787, 'ZAMEL MEW-01', 1, NULL, '2019-07-26 17:31:49', '2020-11-14 20:51:01', 743, 1337556112, 1336017626, 0xfd7c0bdfa07a6f02eac3bf6e7a537b2b, '2.7.8', 10, NULL, '$2a$04$98ZyNmKZVYAXnw/AuuUNHuBxcNuMnRGgGoMVKZuL0nMtDv8j0f2uu', 0, 4, 1000),
(563, 677, 'ZAMEL SBW-01', 1, NULL, '2019-07-29 13:32:47', '2020-11-10 00:28:29', 632, 1299272688, 2987635694, 0xdfba8d7f4da9ed8d8f7d921bde928b87, '2.7.0', 9, NULL, '$2a$04$jABbqMyqelU2IppM16Nxcur2dMUp24QC/VYvmJrhfZVVAYwkRPf/K', 0, 4, 0),
(983, 246, '*Yunshan', 1, NULL, '2019-08-11 11:58:22', '2020-11-14 17:14:21', 239, 1427000160, 1427000160, 0x7e8b0605793cf4d51de4d357b2029d3e, '2.7.2', 7, NULL, '$2a$04$NRNmBfgmQMmDTO/WhvOjyOEkYoUKJKt1doYZJQ37Jq9oqur0KmN32', 0, 0, 0),
(989, 1523, 'ZAMEL SLW-01', 1, NULL, '2019-08-11 17:16:17', '2020-11-15 21:53:54', 1009, 3117203966, 3117203966, 0xed22914dfc2f7d2a087538d17a400422, '2.5.5', 7, NULL, '$2a$04$yAPavDrRL2Rl9obg5e891e0GcVWTnb3PYdhetZLGVOZYcYXQ7aoKG', 0, 4, 0),
(1068, 1623, 'SUPLA-GATE-MODULE', 1, NULL, '2019-08-14 13:05:07', '2020-11-16 14:59:31', 1495, 637050721, 95218934, 0x715c8cb87f0306eeb0ccc39ddfef55d4, '2.5.5', 7, NULL, '$2a$04$H.VOFffbrKhLTvI/EDpq0uZBObHtiIMbdRki3/tb9pcUuv6EKVlbu', 0, 0, 0),
(3195, 1819, 'SONOFF-p4-DHT22 by@Zybi', 1, NULL, '2019-08-25 21:19:35', '2020-11-14 01:04:57', 1645, 1841570477, 1841570477, 0xecf58717844b996fdeb82834ca061ee9, '2.0', 5, 1819, NULL, 0, 6, 0),
(4124, 2999, '8xDSv3.1 by@wojtek', 1, NULL, '2019-09-13 12:54:46', '2019-11-05 11:41:37', 2645, 1308376372, 1308376372, 0x2018103084f3eb9f74ea041234567890, '1.6.1', 9, 2999, NULL, 0, 0, 0),
(4567, 2887, 'Supla-Gate', 0, NULL, '2019-09-18 14:04:48', '2019-11-05 16:39:33', 2288, 1345369950, 1345369950, 0x2018091568c63a97abd6011234567890, '1.6.1', 9, 2887, NULL, 0, 0, 0),
(5761, 2126, 'SONOFF-gate-p5-DS18B20 by@Zybi', 1, NULL, '2019-10-06 13:19:24', '2020-09-27 08:31:10', 1899, 3287873036, 3287873036, 0xd2bee1f5a77643709200e5a1b4d78885, '2.0', 5, 2126, NULL, 0, 6, 0),
(5823, 1530, 'WEMOS-ROLLER-SHUTTER-UNI by@Zybi', 1, NULL, '2019-10-07 16:10:18', '2019-10-20 12:04:29', 1414, 1392954470, 1392914456, 0x46b3fac81782f352d3f1cca8d8087744, '2.5.3', 7, NULL, '$2a$04$Xqa3OTeZrUPFBunU6RXe3ukWZXOrnSotqyqGPEgcPVi.yJWZbrte6', 0, 0, 0),
(6361, 4339, 'SONOFF-SV by @slawek', 1, NULL, '2019-10-11 20:21:22', '2020-11-16 06:07:12', 3741, 3117557337, 3117557337, 0x75be83627660e046964b3698d58a9f8f, '2.5.5s', 7, NULL, '$2a$04$OdLpkg3PCac323G5H4heT.ad.4MnPDSSN.cTMJYcZgoC9OE0DQgaO', 0, 6, 0),
(6688, 4552, 'Impulse counter RB-03', 1, NULL, '2019-10-26 08:47:46', '2020-11-15 13:53:01', 53, 1539346732, 1539346732, 0x8793f6e5c1133808f07637e0e9325306, '2.7.9', 10, NULL, '$2a$04$mR0dpWEx/jxxauO8QB477O2ELKuwYNnYq23v5Sa0kUSwrY3BYb7zO', 0, 0, 0),
(7212, 458, 'Eco-pea level sensor', 1, NULL, '2019-11-21 13:18:49', '2020-11-15 12:06:14', 431, 3105203164, 524224250, 0x2cf4325e22e3e3225e32f42c00000000, '1.6.1', 9, 458, NULL, 0, 0, 0),
(7878, 1102, 'BME280', 1, NULL, '2020-01-18 13:29:16', '2020-06-20 10:09:15', 1017, 3120425903, 3120425903, 0x201909175002914edadf718290696772, '2.0.0', 9, 1102, NULL, 0, 0, 0),
(9236, 5174, 'HOME', 1, NULL, '2020-06-13 15:36:15', '2020-11-16 08:27:10', 1347, 637065048, 520114222, 0x20181030bcddc2513f79041234567891, '1.6.1', 9, 5174, NULL, 0, 0, 0),
(9344, 2052, 'ZAMEL SBW-02', 1, NULL, '2020-07-03 19:54:35', '2020-11-16 01:00:36', 1840, 637063891, 520111453, 0xef7b79f5a9b9fde48b6b7873da4839e9, '2.7.13', 7, NULL, '$2a$04$rwBg.EzK.6YuCt2vHDkzyejh2q85LknRdzc.Z15N5/DeWLr7wlGaS', 0, 4, 220),
(9480, 3884, 'SMART VALVE PEVEKO', 1, NULL, '2020-07-28 14:27:22', '2020-11-16 04:27:38', 1792, 1358689684, 1358689688, 0xdf5bd2e54991dfa5cefdbf3e5c0093c7, '2.7.18', 11, NULL, '$2a$04$IQUPTpniELIOhmc0fwg7rODffYS8zw5SxBlqySw2fgihkae8RjJeG', 0, 10, 1),
(9665, 5415, 'Weather', 1, NULL, '2020-08-18 19:22:15', '2020-11-16 14:59:02', 3411, 858161490, 858161490, 0x3f915f90e45707432aad21285ac18f5b, '1.0.4', 10, 3935, NULL, 0, 0, 0),
(9717, 5446, 'IMPULSE COUNTER', 1, NULL, '2020-09-04 08:26:21', '2020-11-11 12:41:52', 1802, 1841675552, 3163124292, 0x9487772ebdfdb5b3fe62a55d98c2c74a, '2.7.2', 10, NULL, '$2a$04$bg.jm5FuDPq3fI.Vo2NR0ev3nkDYkO.PhONz/HOh3/3Wrhcy88qFW', 0, 0, 0),
(9934, 4994, 'HEATPOL HOME+', 1, NULL, '2020-09-30 11:43:52', '2020-11-13 07:35:35', 1238, 1317381067, 1317381067, 0x7f0a42dd62697f8e0ddec2467d4ed458, '2.7.25', 11, NULL, '$2a$04$gfoLcSczCHd5PAKGeZ2l4.ve9pWrBNx7CA29fl2cG2e9aAh65iwre', 0, 8, 1),
(10190, 3229, 'SUPLA-Skalar', 1, NULL, '2020-10-28 16:28:42', '2020-11-11 16:23:05', 2487, 1520175582, 1520175582, 0xe94f09da8ebff57e71735226a34443bb, '1.6.1', 9, 3229, NULL, 0, 0, 0),
(10286, 2643, 'GATE', 1, NULL, '2020-11-06 14:51:28', '2020-11-16 09:31:56', 2337, 2609197469, 2609197469, 0xdc4f2278a5dbdcdb4fa52278dbdca54f, '2.3.2/1.11 @lukfud', 12, NULL, '$2a$04$nJ7dljL0wXCnOpNKR85uJ.SbefjKKcORPzgLwj.eJXA3lIpztiQ8a', 0, 0, 0),
(10300, 2643, 'ZAMEL RNW-01', 1, NULL, '2022-01-21 14:30:28', '2022-01-21 14:30:28', 3748, 2609197469, 2609197469, 0xaa4f2278a5dbdcdb4fa52278dbdca54f, '2.8.47', 17, NULL, '$2a$04$nJ7dljL0wXCnOpNKR85uJ.SbefjKKcORPzgLwj.eJXA3lIpzaaQ8a', 0, 0, 0);

INSERT INTO `supla_dev_channel` (`id`, `type`, `func`, `param1`, `param2`, `caption`, `param3`, `text_param1`, `text_param2`, `text_param3`, `user_id`, `channel_number`, `iodevice_id`, `flist`, `alt_icon`, `hidden`, `location_id`, `flags`, `user_icon_id`) VALUES
(20, 2900, 110, 0, 0, NULL, 0, NULL, NULL, NULL, 48, 0, 12, 16, NULL, 0, NULL, 0, NULL),
(23, 3000, 40, 0, 0, NULL, 0, NULL, NULL, NULL, 53, 1, 14, 0, 0, 0, NULL, 0, NULL),
(50, 2900, 140, 0, 0, NULL, 0, NULL, NULL, NULL, 117, 0, 36, 96, 0, 0, NULL, 0, NULL),
(51, 2900, 140, 0, 0, NULL, 0, NULL, NULL, NULL, 117, 1, 36, 96, 0, 0, NULL, 0, NULL),
(56, 2900, 130, 0, 0, NULL, 0, NULL, NULL, NULL, 121, 0, 40, 96, 0, 0, NULL, 0, NULL),
(286, 2900, 20, 1000, 287, NULL, 0, NULL, NULL, NULL, 171, 0, 157, 15, 1, 0, NULL, 0, NULL),
(404, 1000, 70, 403, 0, NULL, 0, NULL, NULL, NULL, 390, 2, 205, 0, 0, 0, NULL, 0, NULL),
(821, 4000, 180, 0, 0, NULL, 0, NULL, NULL, NULL, 676, 0, 411, 0, 0, 0, NULL, 0, NULL),
(966, 5000, 310, 0, 6500, NULL, 0, 'PLN', NULL, NULL, 743, 0, 506, 0, 0, 0, NULL, 0, NULL),
(1055, 2900, 30, 500, 0, 'Long caption test ABCDEGFH', 0, NULL, NULL, NULL, 632, 0, 563, 15, 0, 0, NULL, 0, NULL),
(1835, 2900, 90, 4000, 0, NULL, 0, NULL, NULL, NULL, 239, 0, 983, 239, 0, 0, NULL, 0, NULL),
(1852, 4010, 190, 0, 0, NULL, 0, NULL, NULL, NULL, 1009, 0, 989, 0, 0, 0, NULL, 0, NULL),
(2009, 2900, 10, 1000, 0, 'Gateway II', 0, NULL, NULL, NULL, 1495, 0, 1068, 15, 0, 0, NULL, 0, NULL),
(3068, 3020, 45, 0, 0, NULL, 0, NULL, NULL, NULL, 1645, 1, 3195, 0, 0, 0, NULL, 0, NULL),
(4688, 4020, 200, 0, 0, NULL, 0, NULL, NULL, NULL, 2645, 2, 4124, 0, 0, 0, NULL, 0, NULL),
(5177, 1000, 50, 5175, 0, NULL, 1, NULL, NULL, NULL, 2288, 2, 4567, 0, 0, 0, NULL, 0, NULL),
(7212, 1000, 240, 0, 0, NULL, 0, NULL, NULL, NULL, 1899, 2, 5761, 0, 0, 0, NULL, 0, NULL),
(7341, 1000, 120, 7340, 0, NULL, 0, NULL, NULL, NULL, 1414, 1, 5823, 0, 0, 0, NULL, 0, NULL),
(8453, 1000, 100, 0, 0, NULL, 1, NULL, NULL, NULL, 3741, 1, 6361, 0, 0, 0, NULL, 0, NULL),
(9202, 5010, 330, 0, 0, NULL, 3, NULL, NULL, NULL, 53, 0, 6688, 0, 0, 1, NULL, 0, NULL),
(9203, 5010, 320, 20300, 20500, NULL, 107, 'PLN', NULL, NULL, 53, 1, 6688, 0, 0, 0, NULL, 0, NULL),
(10259, 1020, 210, 0, 0, NULL, 0, NULL, NULL, NULL, 431, 2, 7212, 0, 0, 0, NULL, 0, NULL),
(12048, 3044, 260, 0, 0, NULL, 0, NULL, NULL, NULL, 1017, 0, 7878, 0, 0, 0, NULL, 0, NULL),
(15039, 1000, 80, 0, 0, NULL, 1, NULL, NULL, NULL, 1347, 5, 9236, 0, 0, 0, NULL, 0, NULL),
(15283, 1000, 230, 0, 0, NULL, 0, NULL, NULL, NULL, 1840, 3, 9344, 0, 0, 0, NULL, 0, NULL),
(15596, 7000, 500, 0, 0, NULL, 0, NULL, NULL, NULL, 1792, 0, 9480, 0, 0, 0, NULL, 65536, NULL),
(16054, 3048, 270, 0, 0, NULL, 0, NULL, NULL, NULL, 3411, 2, 9665, 0, NULL, 0, NULL, 0, NULL),
(16055, 3042, 250, 0, 0, NULL, 0, NULL, NULL, NULL, 3411, 3, 9665, 0, NULL, 0, NULL, 0, NULL),
(16166, 5010, 315, 0, 0, NULL, 1000, 'PLN', NULL, NULL, 1802, 0, 9717, 0, 0, 0, NULL, 0, NULL),
(16708, 6010, 410, 0, 0, NULL, 0, NULL, NULL, NULL, 1238, 0, 9934, 0, 0, 0, NULL, 0, NULL),
(17748, 1020, 220, 0, 0, NULL, 0, NULL, NULL, NULL, 2487, 0, 10190, 0, 0, 0, NULL, 0, NULL),
(17749, 1020, 220, 0, 0, NULL, 0, NULL, NULL, NULL, 2487, 1, 10190, 0, 0, 0, NULL, 0, NULL),
(17750, 1020, 220, 0, 0, NULL, 0, NULL, NULL, NULL, 2487, 2, 10190, 0, 0, 0, NULL, 0, NULL),
(18023, 1000, 60, 18022, 0, NULL, 0, NULL, NULL, NULL, 2337, 1, 10286, 0, 0, 0, NULL, 65536, NULL);

INSERT INTO `supla_dev_channel` (`id`, `type`, `func`, `param1`, `param2`, `caption`, `param3`, `text_param1`, `text_param2`, `text_param3`, `user_id`, `channel_number`, `iodevice_id`, `flist`, `alt_icon`, `hidden`, `location_id`, `flags`, `user_icon_id`, `user_config`, `properties`) VALUES
(18100, 11000, 700, 0, 0, NULL, 0, NULL, NULL, NULL, 3748, 0, 10300, 0, 0, 0, NULL, 81920, NULL, '{\"disablesLocalOperation\":[],\"relatedChannelId\":null,\"hideInChannelsList\":false,\"actions\":{\"TOGGLE_X1\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TURN_ON\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X2\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X3\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X4\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X5\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}}}}','{\"actionTriggerCapabilities\":[\"TURN_ON\",\"TURN_OFF\",\"TOGGLE_X1\",\"TOGGLE_X2\",\"TOGGLE_X3\",\"TOGGLE_X4\",\"TOGGLE_X5\"]}'),

(18101, 11000, 700, 0, 0, NULL, 0, NULL, NULL, NULL, 3748, 1, 10300, 0, 0, 0, NULL, 81920, NULL, '{\"disablesLocalOperation\":[],\"relatedChannelId\":null,\"hideInChannelsList\":false,\"actions\":{\"TOGGLE_X1\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TURN_OFF\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X2\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X3\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X4\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X5\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}}}}','{\"actionTriggerCapabilities\":[\"TURN_ON\",\"TURN_OFF\",\"TOGGLE_X1\",\"TOGGLE_X2\",\"TOGGLE_X3\",\"TOGGLE_X4\",\"TOGGLE_X5\"]}'),

(18102, 11000, 700, 0, 0, NULL, 0, NULL, NULL, NULL, 3748, 2, 10300, 0, 0, 0, NULL, 81920, NULL, '{\"disablesLocalOperation\":[],\"relatedChannelId\":null,\"hideInChannelsList\":false,\"actions\":{\"HOLD\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X1\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X2\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X3\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X4\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X5\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}}}}', '{\"actionTriggerCapabilities\":[\"HOLD\",\"SHORT_PRESS_X1\",\"SHORT_PRESS_X2\",\"SHORT_PRESS_X3\",\"SHORT_PRESS_X4\",\"SHORT_PRESS_X5\"]}'),

(18103, 11000, 700, 0, 0, NULL, 0, NULL, NULL, NULL, 3748, 3, 10300, 0, 0, 0, NULL, 81920, NULL, '{\"disablesLocalOperation\":[],\"relatedChannelId\":null,\"hideInChannelsList\":false,\"actions\":{\"HOLD\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X1\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X2\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X3\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X4\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"SHORT_PRESS_X5\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X1\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TURN_OFF\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X2\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X3\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X4\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}},\"TOGGLE_X5\":{\"subjectType\":\"other\",\"action\":{\"id\":10000}}}}', '{\"actionTriggerCapabilities\":[\"HOLD\",\"SHORT_PRESS_X1\",\"SHORT_PRESS_X2\",\"SHORT_PRESS_X3\",\"SHORT_PRESS_X4\",\"SHORT_PRESS_X5\",\"TURN_ON\",\"TURN_OFF\",\"TOGGLE_X1\",\"TOGGLE_X2\",\"TOGGLE_X3\",\"TOGGLE_X4\",\"TOGGLE_X5\"]}'),

(18104, 11000, 700, 0, 0, NULL, 0, NULL, NULL, NULL, 3748, 4, 10300, 0, 0, 0, NULL, 81920, NULL, '', '');


